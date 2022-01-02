#include "bookworm_ai_methods.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <chrono>
#include <string>

extern bool debug_mode;
extern bool manual_debug_mode;

static const int kNumPixelPerLetter = 25;

static int colors[NUMC][kNumPixelPerLetter];
static bool colors_initialized = false;

static bool read_colors(FILE *fin, int *result) {
	// Read the colors of the pixels in the file |fin|.
	// Returns if the colors are successfully read.
	static char buffer[kNumPixelPerLetter * 2 + 5];
	if (!fin) {
		return false;
	}
	memset(buffer, 0, sizeof(buffer));
	fgets(buffer, sizeof(buffer), fin);
	if (debug_mode) {
		printf("Colors: %s\n", buffer);
	}
	for (int i = 0; i < kNumPixelPerLetter; i++) {
		if (buffer[i * 2] >= '0' && buffer[i * 2] <= '9') {
			result[i] = buffer[i * 2] - '0';
		} else if (buffer[i * 2] >= 'A' && buffer[i * 2] <= 'F') {
			result[i] = buffer[i * 2] - 'A' + 10;
		} else {
			return false;
		}
		if (buffer[i * 2 + 1] >= '0' && buffer[i * 2 + 1] <= '9') {
			result[i] = result[i] * 16 + buffer[i * 2 + 1] - '0';
		} else if (buffer[i * 2 + 1] >= 'A' && buffer[i * 2 + 1] <= 'F') {
			result[i] = result[i] * 16 + buffer[i * 2 + 1] - 'A' + 10;
		} else {
			return false;
		}
	}
	return true;
}

static const char *color_string(int *col) {
	std::string result;
	static char buffer[16];
	for (int i = 0; i < kNumPixelPerLetter; i++) {
		if (debug_mode) {
			printf("%d: %d\n", i, col[i]);
		}
		sprintf(buffer, "%02X", col[i]);
		result += std::string(buffer);
	}
	return result.c_str();
}

static bool initialize_initial_letter(bool re_initialize) {
	// Return if |initialize_color_of_initial_letter.ahk| is invoked.
	bool invoked = false;
	if (re_initialize) {
		printf("Re-initializing the colors of initial letters...\n");
		fflush(stdout);
		system("ahk.exe initialize_color_of_initial_letter.ahk");
		invoked = true;
	}
	FILE *fin = fopen("color_of_initial_letter.txt", "r");
	if (!fin) {
		printf("Initializing the colors of initial letters...\n");
		fflush(stdout);
		system("ahk.exe initialize_color_of_initial_letter.ahk");
		invoked = true;
		fin = fopen("color_of_initial_letter.txt", "r");
	}
	const int kMaxAttempt = 2;
	int num_attempts = 0;
	do {
		bool ok = true;
		for (int i = 0; i < NUMC; i++) {
			if (!read_colors(fin, colors[i])) {
				ok = false;
				break;
			}
		}
		if (fin) {
			fclose(fin);
		}
		if (ok) {
			return invoked;
		}
		// Failed, retry for <= 1 time
		printf("Failed to initialize the colors of initial letters. Retrying...\n");
		fflush(stdout);
		system("ahk.exe initialize_color_of_initial_letter.ahk");
		invoked = true;
		fin = fopen("color_of_initial_letter.txt", "r");
		num_attempts++;
	} while (num_attempts < kMaxAttempt);
	printf("Cannot initialize the colors of initial letters.\n");
	exit(1);
}

char retrieve_initial_letter(bool &initial_letter_cleared) {
	if (manual_debug_mode) {
		// manually input initial letter
		char ch = getchar();
		while (ch < 'a' || ch > 'z')
			ch = getchar();
		return ch;
	}
	const int kMaxAttempt = 8;
	const int kReInitializeAtAttempt = 5;
	const int kMinErrorThreshold = 32;
	int num_attempts = 0;
	int col[kNumPixelPerLetter];
	initial_letter_cleared = false;
	do {
		if (num_attempts != kReInitializeAtAttempt) {
			system("ahk.exe get_color_of_initial_letter.ahk");
		}
		FILE *fin = fopen("tmp.txt", "r");
		if (!read_colors(fin, col)) {
			printf("Cannot read initial letter.\n");
			exit(1);
		}
		fclose(fin);
		if (!colors_initialized) {
			initial_letter_cleared = initialize_initial_letter(/*re_initialize=*/false);
			colors_initialized = true;
		}
		int min_error_val = 1010101010, min_error_i = 0;
		for (int i = 0; i < NUMC; i++) {
			// tolerate small errors
			int current_error = 0;
			for (int j = 0; j < kNumPixelPerLetter; j++) {
				current_error += abs(col[j] - colors[i][j]);
			}
			if (current_error < min_error_val) {
				min_error_val = current_error;
				min_error_i = i;
			}
			if (current_error == 0) {
				return 'a' + i;
			}
		}
		if (min_error_val <= kMinErrorThreshold) {
			if (debug_mode) {
				printf("Small error at initial letter tolerated (color=%s, expected=%s)\n",
					color_string(col), color_string(colors[min_error_i]));
			}
			return 'a' + min_error_i;
		}
		if (initial_letter_cleared) {
			break;  // Unable to try again
		}
		num_attempts++;
		// Attempt multiple times to avoid the multicolor floating characters
		if (num_attempts == kReInitializeAtAttempt) {
			initial_letter_cleared = initialize_initial_letter(/*re_initialize=*/true);
		}
	} while (num_attempts < kMaxAttempt);
	printf("Cannot parse initial letter (color=%s).\n", color_string(col));
	exit(1);
}

void pause_until_enter() {
	system("ahk.exe pause_until_enter.ahk");
}

void perform_guess(const char *guess_word, int remaining_guesses, char *known_letters, bool *last_gold) {
	const int kLetterCoolDown = 700;  // We need to wait 700ms to press the same letter again.
	const int kSlotCoolDown = 100;  // We need to wait 100ms to load a letter to a just unloaded slot.
	static std::chrono::time_point<std::chrono::steady_clock> last_press[26];
	if (!guess_word) {
		// initialize the array |last_press|
		for (int i = 0; i < NUMC; i++) {
			last_press[i] = std::chrono::steady_clock::now() - std::chrono::milliseconds(kLetterCoolDown);
		}
		return;
	}
	if (remaining_guesses > MAX_GUESS) {
		// Initial letter is cleared.
		for (int i = 1; i < WORD_LEN; i++) {
			last_gold[i] = false;
		}
	} else if (remaining_guesses == MAX_GUESS) {
		for (int i = 1; i < WORD_LEN; i++) {
			last_gold[i] = false;
		}
		last_gold[0] = true;
	}
	FILE *fout = fopen("tmp.txt", "w");
	fprintf(fout, "%d\n", MAX_GUESS - remaining_guesses);
	for (int i = 0; i < WORD_LEN; i++) {
		// i-th letter
		int letter_before = last_gold[i] ? (int)(known_letters[i] - 'a') : -1;
		int letter_after = (int)(guess_word[i] - 'a');
		if (letter_before != letter_after && letter_before != -1) {
			// We need to remove the wrong letter here.
			fprintf(fout, "1\n");
		} else {
			fprintf(fout, "0\n");
		}
	}
	std::chrono::time_point<std::chrono::steady_clock> current_time = std::chrono::steady_clock::now();
	const std::chrono::time_point<std::chrono::steady_clock> after_removal_time = std::chrono::steady_clock::now();
	for (int i = 0; i < WORD_LEN; i++) {
		// i-th letter
		int letter_before = last_gold[i] ? (int)(known_letters[i] - 'a') : -1;
		int letter_after = (int)(guess_word[i] - 'a');
		int cooldown = 0;
		if (letter_before == letter_after) {
			fprintf(fout, "0\n");  // zero cooldown
			fprintf(fout, "-1\n");  // no need to press any letter
			continue;
		}
		
		if (std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_press[letter_after]).count() < kLetterCoolDown) {
			cooldown = kLetterCoolDown - std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_press[letter_after]).count();
			current_time += std::chrono::milliseconds(cooldown);
		}
		if (letter_before != -1 && std::chrono::duration_cast<std::chrono::milliseconds>(current_time - after_removal_time).count() < kSlotCoolDown) {
			int cooldown_diff = kSlotCoolDown - std::chrono::duration_cast<std::chrono::milliseconds>(current_time - after_removal_time).count();
			current_time += std::chrono::milliseconds(cooldown_diff);
			cooldown += cooldown_diff;
		}
		last_press[letter_after] = current_time;
		fprintf(fout, "%d\n", cooldown);  // cooldown
		fprintf(fout, "%d\n", letter_after);  // the letter to press
	}
	fclose(fout);
	if (manual_debug_mode) {
		// do not invoke ahk
		return;
	}
	system("ahk.exe perform_guess.ahk");
}

bool input_gold_silver(bool *gold, bool *silver) {
	static char buf[20];
	scanf("%10s", buf);  // only first 5 characters are needed
	if (strlen(buf) != WORD_LEN) {
		// correct guess
		return false;
	}
	for (int k = 0; k < WORD_LEN; k++) {
		gold[k] = buf[k] == 'g';
		silver[k] = buf[k] == 's';
	}
	return true;
}

bool retrieve_guess_result(int remaining_guesses, bool *gold, bool *silver) {
	if (manual_debug_mode) {
		return input_gold_silver(gold, silver);
	}
	FILE *fout = fopen("tmp.txt", "w");
	fprintf(fout, "%d", MAX_GUESS - remaining_guesses);  // "\n" at the end is not accepted in autohotkey
	fclose(fout);
	Sleep(100);  // wait for the color to be correct
	system("ahk.exe retrieve_guess_result.ahk");
	FILE *fin = fopen("tmp.txt", "r");
	char buf[64];
	if (fscanf(fin, "%s", buf) != 1) {
		printf("Cannot read guess result.\n");
		exit(1);
	}
	if (strlen(buf) != WORD_LEN) {
		printf("Cannot parse guess result.\n");
		exit(1);
	}
	for (int i = 0; i < WORD_LEN; i++) {
		if (buf[i] == '0') {
			// Empty slot means already correct.
			return false;
		} if (buf[i] == '5' || buf[i] == '4' || buf[i] == '6') {
			gold[i] = silver[i] = false;
		} else if (buf[i] == 'E' || buf[i] == 'F' || buf[i] == 'D') {
			silver[i] = true;
			gold[i] = false;
		} else if (buf[i] == '9' || buf[i] == 'A' || buf[i] == '8' || buf[i] == 'B') {
			gold[i] = true;
			silver[i] = false;
		} else {
			printf("Cannot parse guess result at %d: %c\n", i, buf[i]);
		}
	}
	return true;
}
