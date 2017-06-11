#VARIABLES
set nobeep
set fignore = ( .o .out )
set path = (~/bin /bin /sbin /usr/{bin,sbin,X11R6/bin,local/bin,local/sbin,games} .)
set filec
set history = 1000
set ignoreeof
set mail = (/var/mail/$USER)
set mch = `hostname -s`

#ENVIRONMENT
setenv CC clang
setenv CXX clang++

#ALIAS
alias weather curl -4 wttr.in/quebec
alias we weather
alias cc clang
alias c++ clang++
alias cxx clang++
alias emacs emacs -nw
alias df	df -k
alias du	du -k
alias f		finger
alias h		'history -r | more'
alias j		jobs -l
alias la	ls -a
alias lf	ls -FA
alias ll	ls -lsA
alias tset	'set noglob histchars=""; eval `\tset -s \!*`; unset noglob histchars'
alias z		suspend
alias prompt 'set prompt = "$mch:q"":$user""{\!}"" ($cwd)% "'
alias cd 'cd \!*; prompt'
alias chdir 'cd \!*; prompt'
alias popd 'popd \!*; prompt'
alias pushd 'pushd \!*; prompt'
cd .
umask 22
