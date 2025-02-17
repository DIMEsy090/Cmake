## README

### Тестовое задание 

#### Описание задания

Задание состоит из двух программ, взаимодействующих через использование сокетов.

#### Структура основная проекта

- `CMakeProject1`
  - `CMakeProject1`
    - `CMakeProject1.cpp`
    - `CMakeLists.txt`
    - `CMakeProject1.h`
- `CMakeProject2`
  - `CMakeProject2`
    - `CMakeProject2.cpp`
    - `CMakeLists.txt`
    - `CMakeProject2.h`
- `README.md`

### Сборка и запуск

Для сборки проекта потребуется `cmake` и `gcc`.

#### Сборка

1. Клонируйте репозиторий или распакуйте архив с исходным кодом.
2. Перейдите в директорию `Program1` и выполните следующие команды:

    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

3. Повторите шаг 2 для директории `Program2`.

#### Запуск

1. Запустите `CMakeProject1`:

    ```bash
    ./CMakeProject1/build/CMakeProject1
    ```

2. Запустите `Program2`:

    ```bash
    ./CMakeProject2/build/CMakeProject2
    ```

### Описание программ

#### Программа №1

Программа состоит из двух потоков и общего буфера.

- **Поток 1:**
  - Принимает строку, введенную пользователем.
  - Проверяет, что строка состоит только из цифр и не превышает 64 символов.
  - Сортирует строку по убыванию.
  - Заменяет четные элементы на "KV".
  - Помещает обработанную строку в общий буфер и ожидает следующего ввода.

- **Поток 2:**
  - Обрабатывает данные из общего буфера.
  - Выводит полученные данные на экран.
  - Рассчитывает сумму всех числовых значений в строке.
  - Передает сумму в Программу №2.
  - Ожидает следующие данные.

#### Программа №2

- Ожидает данные от Программы №1.
- При получении данных анализирует длину переданного значения.
  - Если длина больше 2 символов и кратна 32, выводит сообщение о полученных данных.
  - Иначе выводит сообщение об ошибке.
- Ожидает следующие данные.

