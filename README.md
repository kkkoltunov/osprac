# :label: Небольшие программы из курса по операционным системам. 2 курс Вышки.
Здесь собраны все программы и задания к ним, которые были написаны мной на 2 курсе во время прохождения дисциплины Операционные системы.

:floppy_disk: использовалась Ubuntu 20.04 для доступа к различным системным штукам.

Далее коротко о тематике каждого семинара.

## :cd: [Семинары 1–2. Знакомство с операционной системой UNIX](/Sem01-02)

### Задача 1:
Напишите, откомпилируйте и запустите программу, которая печатала бы идентификатор пользователя, запустившего программу, и идентификатор его группы.

## :cd: [Семинары 3-4. Процессы в ОС UNIX](/Sem03-04)

### Задача 1:
Напишите программу, печатающую значения PID и PPID для текущего процесса. Запустите её несколько раз подряд. Посмотрите, как меняется идентификатор текущего процесса. Объясните наблюдаемые изменения.

### Задача 2:
Отредактировать пример 1 так, чтобы сделать поведение двух процессов различным.

### Задача 3:
Напишите программу, распечатывающую значения аргументов командной строки и параметров окружающей среды для текущего процесса.

### Задача 4:
Модифицируйте программу, созданную при выполнении задачи 2 так, чтобы порождённый процесс запускал на исполнение новую (любую) программу.

## :cd: [Семинары 5-6. Организация взаимодействия через pipe и FIFO](/Sem05-06)

### Задача 1:
Измените программу 05-1.c так, чтобы она читала записанную ранее в файл информацию и печатала её на экране. Все лишние операторы желательно удалить.

### Задача 2:
Модифицируйте программу 05-3.с для организации такой двусторонней связи.

### Задача 3:
Определите размер pipe для вашей операционной системы.

### Задача 4:
Напишите на базе предыдущего примера две программы, одна из которых пишет информацию в FIFO, а вторая – читает из него, так чтобы между ними не было ярко выраженных родственных связей (т. е. чтобы ни одна из них не была потомком другой).

## :cd: [Семинары 7-8. System V IPC. Разделяемая память и нити исполнения](/Sem07-08)

### Задача 1:
Напишите две программы, осуществляющие взаимодействие через разделяемую память. Первая программа должна создавать сегмент разделяемой памяти и копировать туда собственный исходный текст, вторая программа должна брать оттуда этот текст, печатать его на экране и удалять сегмент разделяемой памяти из системы.

### Задача 2:
Модифицируйте программу 07-2.c, добавив к ней третью нить исполнения.

## :cd: [Семинары 9-10. Семафоры](/Sem09-10)

### Задача 1:
Измените предыдущие программы, так чтобы первая программа (09-1a.c) могла работать без блокировки после не менее 5 запусков второй программы (09-1b.c).

### Задача 2:
На прошлом занятии вы установили, что любые неатомарные операции, связанные с изменением содержимого разделяемой памяти, представляют собой критическую секцию процесса или нити исполнения. Модифицируйте программы 07-3a.c и 07-3b.c, которые иллюстрировали некорректное взаимодействие процессов через разделяемую память, обеспечив с помощью одного IPC семафора взаимоисключения для их правильной работы.

### Задача 3:
Взяв за основу программу 05-3.с, реализуйте поочередную неоднократную передачу информации между ребёнком и родителем через один pipe в двух направлениях, используя ровно один IPC семафор. Считать, что сначала родитель передает данные ребёнку, а затем получает данные от него. Количество пар передача и приём данных в родителе и пар приём и передача в ребёнке равно N ≥ 2. Значение N вводится в родителе с клавиатуры до порождения ребёнка. Число N потенциально может быть достаточно большим и превышать максимально возможное значение семафора, поэтому использовать значение N в операциях над семафором не разрешается.

## :cd: [Семинары 11-12. Очереди сообщений](/Sem11-12)

### Задача 1:
Для полной передачи информативной части сообщения в качестве длины нужно указывать не сумму длин полей, а полную длину структуры, описывающей информативную часть сообщения. Модифицируйте предыдущие программы 11-1a.c и 11-1b.c для передачи сообщений, содержащих полезную нагрузку из комбинированных типов.

### Задача 2:
Напишите программы, осуществляющие двустороннюю связь через одну очередь сообщений.

### Задача 3:
Напишите 2 программы для предложенной схемы мультиплексирования сообщений: клиент и сервер. Клиент вводит с клавиатуры число с плавающей точкой и отправляет серверу. Дожидается от сервера ответа на запрос – это будет число с плавающей точкой – и печатает его на экране. Сервер принимает от клиентов запросы. Полученное от клиента число возводится в квадрат, и результат отправляется клиенту.

## :cd: [Семинар 13. Файловые системы](/Sem13)

### Задача 1:
Напишите программу, определяющую глубину рекурсии для символьных связей при открытии файлов. При запуске программа должна создавать некоторый регулярный файл, допустим, с именем «а». Затем она должна создать символьную связь с именем, предположим, «аа» на файл «a» и попытаться открыть файл «аа». Если это удалось, то должна создаваться символьная связь с именем, скажем, «аб» на файл «аа» и производиться попытка открытия файла «аб». И так далее, пока открыть файл вам не удастся. Это и будет означать, что вы достигли глубины рекурсии (количества допустимых символьных связей) при открытии файла. Значение глубины рекурсии должно быть выведено на экран.


## :cd: [Семинары 14-15. Сигналы](/Sem14-15)

### Задача 1:
Модифицируйте программу из предыдущего примера так, чтобы она перестала реагировать и на нажатие клавиш <ctrl> и <4>. Откомпилируйте и запустите её, убедитесь в отсутствии её реакций на внешние раздражители. Снимать программу придётся теперь с другого терминала командой kill. Узнать идентификаторы своих работающих процессов можно с помощью команды ps -a.

### Задача 2:
Модифицируйте программу из предыдущего примера так, чтобы она печатала сообщение и об нажатии клавиш <ctrl> и <4>. На разные комбинации клавиш должны печататься разные сообщения. Используйте одну и ту же функцию для обработки сигналов SIGINT и SIGQUIT. Откомпилируйте и запустите её, убедитесь в правильной работе. Снимать программу также придётся с другого терминала командой kill.

### Задача 3:
К счастью, для сигнала SIGCHLD последняя проблема с надёжностью может быть легко разрешена. Модифицируйте обработку этого сигнала в программе 14-6.c, так, чтобы процесс-родитель все-таки сообщал о статусе всех завершившихся детей. Изменять в программе можно только обработчик сигнала, используя только сведения текущего семинара, без всяких POSIX сигналов!

### Задача 4:
Необходимо написать две взаимодействующие программы – передатчик и приёмник, которые будут запускаться с разных терминалов. Каждая программа вначале печатает свой PID и вводит с клавиатуры PID собеседника. PID вводится, естественно, пользователем, порядок ввода должен не иметь значения. Программа-передатчик запрашивает с клавиатуры ввод целого числа (число может быть и отрицательным!). Введённое число побитово передаётся программе-приемнику с использованием пользовательских сигналов SIGUSR1 и SIGUSR2. Программа-приёмник после завершения приёма печатает принятое число.
