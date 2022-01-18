#ifndef __BOOKWORM_AI_METHODS_H__
#define __BOOKWORM_AI_METHODS_H__

const char *guess(int num_testcase, int remaining_guesses, char initial_letter, bool *gold, bool *silver, char *&known_letters);
void init(int num_scramble, const char *scramble);
char retrieve_initial_letter(bool &initial_letter_cleared);
void pause_until_enter();
void perform_guess(const char *guess_word, int remaining_guesses, char *known_letters, bool *last_gold);
bool retrieve_guess_result(int remaining_guesses, bool *gold, bool *silver);

const int WORD_LEN = 5;
const int MAX_GUESS = 5;
const int NUMC = 26;
const int NUM_SCRAMBLE = 7828;
const int win_points[MAX_GUESS] = {500, 1000, 2500, 5000, 10000};  // win_points[i] = points for a correct guess with i remaining guesses

#endif
