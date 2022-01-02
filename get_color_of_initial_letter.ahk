#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
; SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.  ; UNRELIABLE!!!!!
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.

; scramble area before scaling
sx0 := 390
sy0 := 239
sd0 := 89

; first letter in scramble area before scaling
fxmn0 := 400
fymn0 := 200
fsize0 := 30

WinGetPos, X, Y, W, H, A
scale := W / 1209.0  ; get the display scale divided by 150% (width=1209)

; scramble area after scaling
sx := Round(sx0 * scale)
sy := Round(sy0 * scale)
sd := sd0 * scale

; first letter in scramble area after scaling
fxmn := Round(fxmn0 * scale)
fymn := Round(fymn0 * scale)
fsize := fsize0 * scale
fn := 5
fd := Round(fsize / (fn - 1))

join(strArray) {
	s := ""
	for i,v in strArray
		s .= substr(v, 7)  ; the last 2 characters
		; s .= ", " . v
	return s
}

stdout := FileOpen("tmp.txt", "w")

check_initial_letter() {
	global
	
	col := []
	j := 0
	Loop {
		i := 0
		Loop {
			PixelGetColor, C, % fxmn + i * fd, % fymn + j * fd
			col[j * fn + i] := C
			i += 1
		} Until i >= fn
		j += 1
	} Until j >= fn
	stdout.WriteLine(join(col))
	return col
}

check_initial_letter()
ExitApp

Esc::
Sleep, 30000  ; enough time to kill the C++ program
ExitApp
