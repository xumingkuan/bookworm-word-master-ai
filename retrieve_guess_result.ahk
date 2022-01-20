#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
; SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.  ; UNRELIABLE!!!!!
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.


; scramble area before scaling
sx0 := 390
sy0 := 239
sd0 := 89
sdy0 := 90

WinGetPos, X, Y, W, H, A
scale := W / 1209.0  ; get the display scale divided by 150% (width=1209)

; scramble area after scaling
sx := Round(sx0 * scale)
sy := Round(sy0 * scale)
sd := sd0 * scale
sdy := sdy0 * scale

join(strArray) {
	s := ""
	for i,v in strArray
		; s .= ", " + v
		s .= substr(v, 3, 1)
	return s
}

FileRead, line_number, tmp.txt

retrieve_guess_result() {
	global
	
	col := []
	i := 0
	Loop {
		PixelGetColor, C, % sx + i * sd, % sy + line_number * sdy
		col[i] := C
		i += 1
	} Until i >= 5
	; OutputDebug, % col
	stdout := FileOpen("tmp.txt", "w")
	stdout.WriteLine(join(col))
}

retrieve_guess_result()
ExitApp

Esc::
Sleep, 30000  ; enough time to kill the C++ program
ExitApp
