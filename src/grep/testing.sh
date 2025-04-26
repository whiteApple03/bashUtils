#!/bin/bash

SUCCESS=0
FAIL=0

# Массив флагов grep для тестирования
flags=(
    ""      # Без флагов
    "-e hello" # Опция -e
    "-i"    # Опция -i (игнорирование регистра)
    "-v"    # Опция -v (инвертирование)
    "-c"    # Опция -c (количество совпадений)
    "-l"    # Опция -l (только имена файлов)
    "-n"    # Опция -n (номер строки)
    "-h"    # Опция -h (не печатать имена файлов)
    "-s"    # Опция -s (не показывать ошибки)
    "-o"    # Опция -o (показывать только совпадения)
    "-e hello -i"
    "-e hello -v"
    "-i -v"
    "-n -i"
     "-n -v"
    "-l -v"
     "-o -i"
     "-o -v"
     "-c -i"
      "-c -v"
     "-h -i"
     "-h -v"
      "-s -i"
      "-s -v"
     "-f pattern.txt  -i"
     "-f pattern.txt -o -v -i"
     "-f pattern.txt -v"
     "-i -v -n -l -o -h -s -c"  # Все вместе, как проверка для крайнего случая
)

# Создаем файл с шаблоном для тестирования опции -f
echo "hello 
sef


" > pattern.txt
# Создаем тестовые файлы
echo "hello world" > test.txt
echo "Hello universe" > test2.txt
echo "goodbye" > test3.txt


for flag in "${flags[@]}"; do
  echo "Тестирование флага: $flag"
  
  # Запускаем s21_grep и grep, сохраняя вывод
  ./s21_grep $flag "test.txt" "test2.txt" "test3.txt" > s21.txt 2> /dev/null
  # valgrind --tool=memcheck --leak-check=yes  ./s21_grep  $flag "test.txt" "test2.txt" "test3.txt" >> leaks
  grep $flag "test.txt" "test2.txt"  "test3.txt" > grep.txt 2> /dev/null

  # Сравниваем выводы
  diff s21.txt grep.txt > /dev/null

  # Анализируем результат
  if [ $? -eq 0 ]; then
    ((SUCCESS++))
    echo "  [OK]"
  else
    ((FAIL++))
    echo "  [FAIL]"
  fi
done

# Выводим результаты
echo "-------------------------"
echo "Успешно: $SUCCESS"
echo "Провалено: $FAIL"

rm test.txt test2.txt test3.txt pattern.txt s21.txt grep.txt