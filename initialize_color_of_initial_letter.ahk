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

; letter area after scaling
lx := Round(lx0 * scale)
ly := Round(ly0 * scale)
ld := ld0 * scale

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

stdout := FileOpen("color_of_initial_letter.txt", "w")

check_initial_letter() {
	global
	
	; MouseMove % fx0, % fy0, 0.1
	; Click
	
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
	; OutputDebug, % col
	stdout.WriteLine(join(col))
	return col
}

MouseMove, sx, sy, 0.1  ; Remove the initial letter.
Click
Sleep, 600  ; Wait to prevent bugs when the initial letter is "a".
lj := 0
Loop {
	li := 0
	Loop {
		MouseMove, sx, sy, 0.1
		Click
		Sleep, 100
		MouseMove, % Round(lx + ld * li), % Round(ly + ld * lj), 0.1
		Click
		Sleep, 100
		check_initial_letter()
		li += 1
	} Until li >= 13
	lj += 1
} Until lj >= 2

MouseMove, sx, sy, 0.1  ; Remove the initial letter.
Click
Sleep, 700  ; Wait to prevent bugs when the initial letter is "z".
ExitApp

Esc::
Sleep, 30000  ; enough time to kill the C++ program
ExitApp
