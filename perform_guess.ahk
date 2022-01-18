#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
; SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.  ; UNRELIABLE!!!!!
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.


; scramble area before scaling
sx0 := 390
sy0 := 239
sd0 := 89

; letter area before scaling
lx0 := 150
ly0 := 730
ld0 := 75

WinGetPos, X, Y, W, H, A
scale := W / 1209.0  ; get the display scale divided by 150% (width=1209)

; scramble area after scaling
sx := Round(sx0 * scale)
sy := Round(sy0 * scale)
sd := sd0 * scale

; letter area after scaling
lx := Round(lx0 * scale)
ly := Round(ly0 * scale)
ld := ld0 * scale

sy_now := sy  ; current line
sx_now := sx  ; first letter

submit_x0 := 490
submit_y0 := 900

submit_x := Round(submit_x0 * scale)
submit_y := Round(submit_y0 * scale)


line_number := 0
letter_before := -1
letter_after := -1
clicked_time := []
letter_cooldown := 600  ; wait 600ms for the same letter
current_time := letter_cooldown

letter_id := 0
Loop {
	clicked_time[letter_id] := 0
	letter_id += 1
} Until letter_id >= 26

Loop, read, tmp.txt
{
	if (line_number = 0) {
		sy_now := sy + sd * A_LoopReadLine
		; MsgBox, %sy_now%
	} else if (line_number <= 5) {
		if (A_LoopReadLine = 1) {
			MouseMove, sx_now, sy_now, 0.1  ; remove the current wrong letter
			Click
		}
		sx_now := sx_now + sd
	} else if (Mod(line_number, 2) == 0) {
		Sleep, A_LoopReadLine  ; cooldown
	} else {
		letter_after := A_LoopReadLine
		if (letter_after >= 0) {
			y := ly + ld * (letter_after // 13)
			x := lx + ld * Mod(letter_after, 13)
			MouseMove, x, y, 0.1
			Click
		}
	}
	if (line_number = 15) {
		; last line
		Sleep, 100  ; prevent bug at the 5th letter
	}
	line_number += 1
}
MouseMove, submit_x, submit_y, 0.1
Click
;  MouseMove, % sx_now - sd, sy_now, 0.1  ; prevent bug at the 5th letter
;  Click

ExitApp

Esc::
Sleep, 30000  ; enough time to kill the C++ program
ExitApp
