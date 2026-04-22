@echo off 
git add . 
set /p msg="请输入本次提交的描述: " 
git commit -m "%%msg%%" 
git push 
pause
