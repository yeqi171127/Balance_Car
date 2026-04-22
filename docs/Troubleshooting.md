\# 平衡小车调试问题记录



\## 2026-04-23：Git 推送时遇到 "LF will be replaced by CRLF" 警告



\### 现象

使用 `git add .` 时提示警告。



\### 原因

Windows 系统使用 CRLF 换行，而 Git 默认在提交时转换为 LF，检出的再转回 CRLF。



\### 解决方案

无需处理，Git 自动处理跨平台换行符，不影响代码功能。若想消除警告可执行 `git config --global core.autocrlf true`。



\### 参考链接

\- \[Git 官方文档 - 换行符处理](https://git-scm.com/book/zh/v2/自定义-Git-配置-Git)

