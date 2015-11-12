#!/bin/zsh

#* * * * * * * * * * * * * * * * * *
#* Henrique Noronha Facioli        *
#* RA : 157986                     *
#* henrique.facioli@gmail.com      *
#* henrique.facioli@ic.unicamp.br  *
#* github : henriquefacioli        *
#* tester                          *
#* * * * * * * * * * * * * * * * * */
#Very simple script just to check if the ias-as is working properly with correct tests

echo "Iniciando testes...\n"
for file in tests/corretos/*.txt
do
    echo "______________________________"
    ./ias-as $file ${file}.res
    echo "Diferencas entre ${file}.hex e ${file}.res :\n"
    diff ${file}.hex ${file}.res
    rm -r tests/corretos/*.res
done
