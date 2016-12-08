@echo off

if exist "%~1\" (
	rem フォルダの場合
	set FOLDER=%~1\
) else (
	set FOLDER=%~dp1
)

echo %FOLDER%
rem pause
rem サブディレクトリも検索
rem for /R %FOLDER% %%i in (*.cpp;*.h) do (
rem カレントディレクトリのみ
for %%i in (%FOLDER%*.cpp;%FOLDER%*.h) do (
	Call %~dp0\encode.exe "-g" %%i
)
echo 終了
pause