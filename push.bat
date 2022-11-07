set /p commit=Enter commit statement: %=%
git commit -m "%commit%"
git branch -M main
git push -u origin main
PAUSE