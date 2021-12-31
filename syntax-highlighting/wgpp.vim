" Vim syntax file
" Language: wgpp

" Save this file at ~/.vim/syntax/ as wgpp.vim
" Add on your .vimrc file: autocmd BufRead,BufNewFile *.wgpp set filetype=wgpp

if exists("b:current_syntax")
  finish
endif

syntax keyword wgppTodos TODO XXX FIXME NOTE

" Language keywords
syntax keyword wgppKeywords exit, print

" Comments
syntax region wgppCommentLine start="#" contains=wgppTodos

" Strings
syntax region wgppString start=/\v"/ skip=/\v\\./ end=/\v"/
syntax region wgppString start=/\v'/ skip=/\v\\./ end=/\v'/

" Set highlights
highlight default link wgppTodos Todo
highlight default link wgppKeywords Keyword
highlight default link wgppCommentLine Comment
highlight default link wgppString String

let b:current_syntax = "wgpp"
