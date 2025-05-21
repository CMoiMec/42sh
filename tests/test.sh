#!/bin/bash

function test () {

    i=0
    t=1

    echo -e "\n\e[1;36m------------------------[BUILD CHECKING]------------------------\n\e[0m"; sleep 0.05

        echo -e "\e[1;37mBuild :" ;
        make re > /dev/null 2> /dev/null
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
            exit 0
        fi

    echo -e "\n\n\e[1;36m------------------------[Simple commands]------------------------\n\e[0m"; sleep 0.05
        echo -e "\e[1;37mempty command n°$t :"; sleep 0.05
        (echo -e "") | ./42sh > bashtest/42sh.txt
        (echo -e "") | tcsh > bashtest/tcsh.txt
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

        echo -e "\e[1;37msimle command n°$t :"; sleep 0.05
        (echo -e "ls") | ./42sh > bashtest/42sh.txt
        (echo -e "ls") | tcsh > bashtest/tcsh.txt
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

        echo -e "\e[1;37mgarbage command n°$t :"; sleep 0.05
        (echo -e "no win without fail") | ./42sh > bashtest/42sh.txt 2>&1
        (echo -e "no win without fail") | tcsh > bashtest/tcsh.txt 2>&1
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

        echo -e "\e[1;37mbinary exec n°$t :"; sleep 0.05
        (echo -e "./bashtest/executable") | ./42sh > bashtest/42sh.txt 2>&1
        (echo -e "./bashtest/executable") | tcsh > bashtest/tcsh.txt 2>&1
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

    echo -e "\n\n\e[1;36m-------------------------[TABS AND SPACES]-------------------------\n\e[0m"; sleep 0.05

        commands5=("ls " "ls     " "ls   -a" "ls\t" "ls\t\t\t\t\t" "ls\t\t\t\t\t-a" "ls\t -a" "ls  \t\t \t -a" " " "\t")
        descriptions4=("ls space" "ls spaces" "ls spaces -a" "ls tab" "ls tabs" "ls tabs -a" "ls tab space" "ls tabs spaces -a" "space" "tab")

        for ((index=0; index<${#commands5[@]}; index++)); do
            echo -e "\e[1;37mTest n°$t (${descriptions4[index]}) :"; sleep 0.05
            echo -e "${commands5[index]}" | ./42sh > bashtest/42sh.txt
            echo -e "${commands5[index]}" | tcsh > bashtest/tcsh.txt
            sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
            if [ $? -eq 0 ]; then
                echo -e "\e[1;32mSUCESS\n\e[0m"
                ((i++))
            else
                echo -e "\e[1;31mFAILURE\n\e[0m"
            fi
            ((t++))
        done

    echo -e "\n\n\e[1;36m------------------------[Path handling]------------------------\n\e[0m"; sleep 0.05
        echo -e "\e[1;37mPath changed for /bin/ n°$t :"; sleep 0.05
        (echo -e "setenv PATH /bin/\nls\npwd") | ./42sh > bashtest/42sh.txt 2>&1
        (echo -e "setenv PATH /bin/\nls\npwd") | tcsh > bashtest/tcsh.txt 2>&1
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

        echo -e "\e[1;37mPath changed for randomfolder n°$t :"; sleep 0.05
        (echo -e "setenv PATH /randomfolder/\nls\npwd") | ./42sh > bashtest/42sh.txt 2>&1
        (echo -e "setenv PATH /randomfolder/\nls\npwd") | tcsh > bashtest/tcsh.txt 2>&1
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

        echo -e "\e[1;37mPath changed for NULL n°$t :"; sleep 0.05
        (echo -e "setenv PATH ''/\nls\npwd") | ./42sh > bashtest/42sh.txt 2>&1
        (echo -e "setenv PATH ''/\nls\npwd") | tcsh > bashtest/tcsh.txt 2>&1
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

        echo -e "\e[1;37mNo path in env n°$t :"; sleep 0.05
        (echo -e "unsetenv PATH") | ./42sh > bashtest/42sh.txt 2>&1
        (echo -e "unsetenv PATH") | tcsh > bashtest/tcsh.txt 2>&1
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

    echo -e "\n\n\e[1;36m-------------------------[BUILTIN SETENV & UNSETENV]-------------------------\n\e[0m"; sleep 0.05

        echo -e "\e[1;37mTest n°$t (setenv) :"; sleep 0.05
        (echo -e "setenv bonjour jesuisuntest" && echo -e "env") | ./42sh > bashtest/42sh.txt
        grep "bonjour=jesuisuntest" bashtest/42sh.txt > /dev/null
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

        echo -e "\e[1;37mTest n°$t (unsetenv with special value n°1) :"; sleep 0.05
        (echo -e "unsetenv") | ./42sh 2> bashtest/42sh.txt
        (echo -e "unsetenv") | tcsh 2> bashtest/tcsh.txt
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

        echo -e "\e[1;37mTest n°$t (setenv with special value n°1) :"; sleep 0.05
        (echo -e "setenv 1bonjour jesuisuntest") | ./42sh 2> bashtest/42sh.txt
        (echo -e "setenv 1bonjour jesuisuntest") | tcsh 2> bashtest/tcsh.txt
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

        echo -e "\e[1;37mTest n°$t (setenv with special value n°2) :"; sleep 0.05
        (echo -e "setenv bon/jour jesuisuntest") | ./42sh 2> bashtest/42sh.txt
        (echo -e "setenv bon/jour jesuisuntest") | tcsh 2> bashtest/tcsh.txt
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

        echo -e "\e[1;37mTest n°$t (setenv with special value n°3) :"; sleep 0.05
        (echo -e "setenv b=onjour jesuisuntest") | ./42sh 2> bashtest/42sh.txt
        (echo -e "setenv b=onjour jesuisuntest") | tcsh 2> bashtest/tcsh.txt
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

        echo -e "\e[1;37mTest n°$t (setenv with special value n°4) :"; sleep 0.05
        (echo -e "setenv a b c") | ./42sh 2> bashtest/42sh.txt
        (echo -e "setenv a b c") | tcsh 2> bashtest/tcsh.txt
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

        echo -e "\e[1;37mTest n°$t (unsetenv whit special value n°1) :"; sleep 0.05
        (echo -e "unsetenv a b c") | ./42sh 2> bashtest/42sh.txt
        (echo -e "unsetenv a b c") | tcsh 2> bashtest/tcsh.txt
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

        echo -e "\e[1;37mTest n°$t (unsetenv whit special value n°2) :"; sleep 0.05
        (echo -e "unsetenv HOME") | ./42sh 2> bashtest/42sh.txt
        (echo -e "unsetenv HOME") | tcsh 2> bashtest/tcsh.txt
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

    echo -e "\n\n\e[1;36m-------------------------[BUILTIN CD & CHDIR]-------------------------\n\e[0m"; sleep 0.05

        commands3=("cd" "cd bashtest" "cd .." "cd /")
        descriptions2=("cd" "cd folder" "cd .." "cd /")

        for ((index=0; index<${#commands3[@]}; index++)); do
            echo -e "\e[1;37mTest n°$t (${descriptions2[index]}) :"; sleep 0.05
            (echo -e "${commands3[index]}" && echo -e "pwd") | ./42sh > bashtest/42sh.txt
            (echo -e "${commands3[index]}" && echo -e "pwd") | tcsh > bashtest/tcsh.txt
            sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
            if [ $? -eq 0 ]; then
                echo -e "\e[1;32mSUCESS\n\e[0m"
                ((i++))
            else
                echo -e "\e[1;31mFAILURE\n\e[0m"
            fi
            ((t++))
        done

        commands6=("cd ffecvdzevvsd" "chdir ./42sh" "cd abc def")
        descriptions6=("cd invalid folder" "chdir executable" "cd too many argument")

        for ((index=0; index<${#commands6[@]}; index++)); do
            echo -e "\e[1;37mTest n°$t (${descriptions6[index]}) :"; sleep 0.05
            (echo -e "${commands6[index]}") | ./42sh 2> bashtest/42sh.txt
            (echo -e "${commands6[index]}") | tcsh 2> bashtest/tcsh.txt
            sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
            if [ $? -eq 0 ]; then
                echo -e "\e[1;32mSUCESS\n\e[0m"
                ((i++))
            else
                echo -e "\e[1;31mFAILURE\n\e[0m"
            fi
            ((t++))
        done

        echo -e "\e[1;37mTest n°$t (cd -) :"; sleep 0.05
        (echo -e "pwd" && echo -e "chdir .." && echo -e "pwd" && echo -e "chdir -" && echo -e "pwd" && echo -e "cd -" && echo -e "pwd" && echo -e "cd" && echo -e "pwd" && echo -e "cd -" && echo -e "pwd" && echo -e "cd -" && echo -e "pwd" && echo -e "cd -" && echo -e "pwd" && echo -e "cd -" && echo -e "pwd" && echo -e "cd /" && echo -e "pwd" && echo -e "cd -" && echo "pwd" && echo -e "cd /bin/" && echo -e "pwd") | ./42sh > bashtest/42sh.txt
        (echo -e "pwd" && echo -e "cd .." && echo -e "pwd" && echo -e "chdir -" && echo -e "pwd" && echo -e "cd -" && echo -e "pwd" && echo -e "cd" && echo -e "pwd" && echo -e "cd -" && echo -e "pwd" && echo -e "cd -" && echo -e "pwd" && echo -e "cd -" && echo -e "pwd" && echo -e "cd -" && echo -e "pwd" && echo -e "cd /" && echo -e "pwd" && echo -e "cd -" && echo "pwd" && echo -e "cd /bin/" && echo -e "pwd") | tcsh > bashtest/tcsh.txt
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

        echo -e "\e[1;37mTest n°$t (cd - without env) :"; sleep 0.05
        (echo -e "setenv PATH /bin/" && echo -e "pwd" && echo -e "cd .." && echo -e "pwd" && echo -e "cd -" && echo -e "pwd") | env -i ./42sh > bashtest/42sh.txt
        (echo -e "setenv PATH /bin/" && echo -e "pwd" && echo -e "cd .." && echo -e "pwd" && echo -e "cd -" && echo -e "pwd") | env -i tcsh > bashtest/tcsh.txt
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

    echo -e "\n\n\e[1;36m-------------------------[BUILTIN ALIAS & UNALIAS]-------------------------\n\e[0m"; sleep 0.05
        echo -e "\e[1;37mTest n°$t (simple alias):"; sleep 0.05
        (echo -e "alias titi ls" && echo -e "titi") | ./42sh > bashtest/42sh.txt
        (echo -e "alias titi ls" && echo -e "titi") | tcsh > bashtest/tcsh.txt
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

        echo -e "\e[1;37mTest n°$t (complex alias) :"; sleep 0.05
        (echo -e "alias titi ls -l" && echo -e "titi") | ./42sh > bashtest/42sh.txt
        (echo -e "alias titi ls -l" && echo -e "titi") | tcsh > bashtest/tcsh.txt
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

        echo -e "\e[1;37mTest n°$t (NULL alias) :"; sleep 0.05
        (echo -e "alias titi" && echo -e "titi") | ./42sh > bashtest/42sh.txt 2>&1
        (echo -e "alias titi" && echo -e "titi") | tcsh > bashtest/tcsh.txt 2>&1
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

        echo -e "\e[1;37mTest n°$t (show if alias are correctly saved) :"; sleep 0.05
        (echo -e "unalias ls" && echo -e "unalias grep" && echo -e "alias je suis bo" && echo -e "alias") | ./42sh > bashtest/42sh.txt 2>&1
        (echo -e "unalias *" && echo -e "alias je suis bo" && echo -e "alias") | tcsh > bashtest/tcsh.txt 2>&1
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

        echo -e "\e[1;37mTest n°$t (display specified alias) :"; sleep 0.05
        (echo -e "unalias ls" && echo -e "unalias grep" && echo -e "alias 42 cc" && echo -e "alias" && echo -e "alias 42" && echo -e "alias 42") | ./42sh > bashtest/42sh.txt 2>&1
        (echo -e "unalias *" && echo -e "unalias grep" && echo -e "alias 42 cc" && echo -e "alias" && echo -e "alias 42" && echo -e "alias 42") | tcsh > bashtest/tcsh.txt 2>&1
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

        echo -e "\e[1;37mTest n°$t (replace alias) :"; sleep 0.05
        (echo -e "unalias ls" && echo -e "unalias grep" && echo -e "alias 42 cc" && echo -e "alias" && echo -e "alias 42 bjr" && echo -e "alias") | ./42sh > bashtest/42sh.txt 2>&1
        (echo -e "unalias *" && echo -e "unalias grep" && echo -e "alias 42 cc" && echo -e "alias" && echo -e "alias 42 bjr" && echo -e "alias") | tcsh > bashtest/tcsh.txt 2>&1
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

    echo -e "\n\n\e[1;36m-------------------------[SET & UNSET]-------------------------\n\e[0m"; sleep 0.05
        echo -e "\e[1;37mTest n°$t (set) :"; sleep 0.05
        (echo -e "set bonjour" && echo -e "set") | ./42sh > bashtest/42sh.txt
        grep "bonjour" bashtest/42sh.txt > /dev/null
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))       

        echo -e "\e[1;37mTest n°$t (unset with special value n°1) :"; sleep 0.05
        (echo -e "unset") | ./42sh 2> bashtest/42sh.txt
        (echo -e "unset") | tcsh 2> bashtest/tcsh.txt
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

        echo -e "\e[1;37mTest n°$t (set with special value n°1) :"; sleep 0.05
        (echo -e "set 1bonjour jesuisuntest") | ./42sh 2> bashtest/42sh.txt
        (echo -e "set 1bonjour jesuisuntest") | tcsh 2> bashtest/tcsh.txt
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

        echo -e "\e[1;37mTest n°$t (set with special value n°2) :"; sleep 0.05
        (echo -e "set bon/jour jesuisuntest") | ./42sh 2> bashtest/42sh.txt
        (echo -e "set bon/jour jesuisuntest") | tcsh 2> bashtest/tcsh.txt
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

        echo -e "\e[1;37mTest n°$t (set with special value n°3) :"; sleep 0.05
        (echo -e "set b=onjour jesuisuntest") | ./42sh 2> bashtest/42sh.txt
        (echo -e "set b=onjour jesuisuntest") | tcsh 2> bashtest/tcsh.txt
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

        echo -e "\e[1;37mTest n°$t (set with special value n°4) :"; sleep 0.05
        (echo -e "set a b c") | ./42sh 2> bashtest/42sh.txt
        (echo -e "set a b c") | tcsh 2> bashtest/tcsh.txt
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

        echo -e "\e[1;37mTest n°$t (unset whit special value n°1) :"; sleep 0.05
        (echo -e "unset a b c") | ./42sh 2> bashtest/42sh.txt
        (echo -e "unset a b c") | tcsh 2> bashtest/tcsh.txt
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

        echo -e "\e[1;37mTest n°$t (unset whit special value n°2) :"; sleep 0.05
        (echo -e "unset HOME") | ./42sh 2> bashtest/42sh.txt
        (echo -e "unset HOME") | tcsh 2> bashtest/tcsh.txt
        sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

    echo -e "\n\n\e[1;36m-------------------------[SEPARATOR]-------------------------\n\e[0m"; sleep 0.05

        commands7=("ls;ls" "ls;ls;ls;pwd;pwd;ls -a;pwd")
        descriptions7=("Simple separator" "Avanced separator")

        for ((index=0; index<${#commands7[@]}; index++)); do
            echo -e "\e[1;37mTest n°$t (${descriptions7[index]}) :"; sleep 0.05
            echo -e "${commands7[index]}" | ./42sh 1> bashtest/42sh.txt
            echo -e "${commands7[index]}" | tcsh 1> bashtest/tcsh.txt
            sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
            if [ $? -eq 0 ]; then
                echo -e "\e[1;32mSUCCESS\n\e[0m"
                ((i++))
            else
                echo -e "\e[1;31mFAILURE\n\e[0m"
            fi
            ((t++))
        done

    echo -e "\n\n\e[1;36m-------------------------[PIPE]-------------------------\n\e[0m"; sleep 0.05

        commands7=("ls | grep src" "cat Makefile | wc -l" "ls -a | sort -nrk 5" "ps -u $USER -o pid,vsz,comm | sort -nrk 2 | head -n 5" "cat bashtest/big_input.txt | grep ." "ls |" " | " " | wc -l" "boze | lol" "ls | boum")
        descriptions7=("Simple pipe n°1" "Simple pipe n°2" "Simple pipe n°3" "Advanced pipe" "Big input" "pipe error n°1" "pipe error n°2" "pipe error n°3" "double invalid cmd" "simple invalid cmd")

        for ((index=0; index<${#commands7[@]}; index++)); do
            echo -e "\e[1;37mTest n°$t (${descriptions7[index]}) :"; sleep 0.05
            timeout 10s echo -e "${commands7[index]}" | ./42sh 1> bashtest/42sh.txt
            timeout 10s echo -e "${commands7[index]}" | tcsh 1> bashtest/tcsh.txt
            sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
            if [ $? -eq 0 ]; then
                echo -e "\e[1;32mSUCCESS\n\e[0m"
                ((i++))
            else
                echo -e "\e[1;31mFAILURE\n\e[0m"
            fi
            ((t++))
        done

        commands10=("ls |" "|")
        descriptions10=("Error handling n°1" "Error handling n°2")

        for ((index=0; index<${#commands10[@]}; index++)); do
            echo -e "\e[1;37mTest n°$t (${descriptions10[index]}) :"; sleep 0.05
            echo -e "${commands10[index]}" | ./42sh > bashtest/42sh.txt 2>&1
            echo -e "${commands10[index]}" | tcsh > bashtest/tcsh.txt 2>&1
            sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
            if [ $? -eq 0 ]; then
                echo -e "\e[1;32mSUCCESS\n\e[0m"
                ((i++))
            else
                echo -e "\e[1;31mFAILURE\n\e[0m"
            fi
            ((t++))
        done

    echo -e "\n\n\e[1;36m-------------------------[REDIRECTION]-------------------------\n\e[0m"; sleep 0.05

        commands8=("echo test12345 > output.txt" "echo test12345 >> output.txt" "ls >" "ls >>")
        descriptions8=("Simple right redirection" "Double right redirection" "Simple right empty redirection" "Double right empty redirection")

        for ((index=0; index<${#commands8[@]}; index++)); do
            echo -e "\e[1;37mTest n°$t (${descriptions8[index]}) :"; sleep 0.05
            echo -e "${commands8[index]}" | ./42sh 2> /dev/null
            sleep 0.05
            mv output.txt bashtest/42sh.txt 2> /dev/null
            sleep 0.05
            echo -e "${commands8[index]}" | tcsh 2> /dev/null
            sleep 0.05
            mv output.txt bashtest/tcsh.txt 2> /dev/null
            sleep 0.05
            sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
            if [ $? -eq 0 ]; then
                echo -e "\e[1;32mSUCCESS\n\e[0m"
                ((i++))
            else
                echo -e "\e[1;31mFAILURE\n\e[0m"
            fi
            ((t++))
        done

        commands9=("cat < Makefile" " < Makefile" "cat < ")
        descriptions9=("Simple left redirection" "No command for left redirection" "Nothing to redirect for simple left redirection")

        for ((index=0; index<${#commands9[@]}; index++)); do
            echo -e "\e[1;37mTest n°$t (${descriptions9[index]}) :"; sleep 0.05
            echo -e "${commands9[index]}" | ./42sh 1> bashtest/42sh.txt 2>&1
            echo -e "${commands9[index]}" | tcsh 1> bashtest/tcsh.txt 2>&1
            sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
            if [ $? -eq 0 ]; then
                echo -e "\e[1;32mSUCCESS\n\e[0m"
                ((i++))
            else
                echo -e "\e[1;31mFAILURE\n\e[0m"
            fi
            ((t++))
        done

    echo -e "\n\n\e[1;36m-------------------------[ERROR HANDLING]-------------------------\n\e[0m"; sleep 0.05

        echo -e "\e[1;37mTest n°$t (Bin not compatible) :"; sleep 0.05
        (echo -e "bashtest/wa") | ./42sh 2> bashtest/42sh.txt
        sdiff -s bashtest/42sh.txt bashtest/wa.txt
        if [ $? -eq 0 ]; then
            echo -e "\e[1;32mSUCESS\n\e[0m"
            ((i++))
        else
            echo -e "\e[1;31mFAILURE\n\e[0m"
        fi
        ((t++))

        commands6=("bashtest/segv" "bashtest/valgrind_output")
        descriptions5=("SegFault with core dump" "exec a directory")

        for ((index=0; index<${#commands6[@]}; index++)); do
            echo -e "\e[1;37mTest n°$t (${descriptions5[index]}) :"; sleep 0.05
            echo -e "${commands6[index]}" | ./42sh 2> bashtest/42sh.txt
            echo -e "${commands6[index]}" | tcsh 2> bashtest/tcsh.txt
            sdiff -s bashtest/42sh.txt bashtest/tcsh.txt
            if [ $? -eq 0 ]; then
                echo -e "\e[1;32mSUCCESS\n\e[0m"
                ((i++))
            else
                echo -e "\e[1;31mFAILURE\n\e[0m"
            fi
            ((t++))
        done

    rm bashtest/42sh.txt
    rm bashtest/tcsh.txt
    ((t--))
    echo -e "\n\e[1;37m--------------------------- RESULTS --------------------------\e[0m"
    echo -e "\e[1;37m|                                                            |\e[0m"
    if [ $i -eq $t ]; then
        echo -e "\e[1;37m|                      ALL TESTS PASSED                      |\e[0m"
    else
        echo -e "\e[1;37m                       $i / $t test passed\e[0m"
    fi
    echo -e "\e[1;37m|                                                            |\e[0m"
    echo -e "\e[1;37m--------------------------------------------------------------\e[0m\n"
}

test
