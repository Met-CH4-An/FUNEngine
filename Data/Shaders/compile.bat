@echo off

SET _subDir = sprv/

cd %CD%

for %%i in (*.vert) do (
	glslangValidator.exe %%i -V -o %%i.spv
)
for %%i in (*.frag) do (
	glslangValidator.exe %%i -V -o %%i.spv
)
for %%i in (*.spv) do (
	move /y %%i sprv/%%i
)
pause