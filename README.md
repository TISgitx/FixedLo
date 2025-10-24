#Инфа о FixedLO

FixedLO — работа над ошибками в текущей реализации Lo. Автор может при этом сам соединить мои изменения со своим основным репозиторием, после того как я посчитаю что код полностью закончен и в него добавить нечего.

# 📘 LO Language — Документация по синтаксису

LO — минималистичный язык с поддержкой переменных, функций и выражений. Ниже представлен полный синтаксис.

---

## 🔹 Переменные

### Объявление

```lo

loc <name> = <type>(<value>)!

Примеры:

print-- "hello, lo!"!

loc x = int(5)!
loc y = str("hello, world!")!

print-- y!
```
> Переменные нельзя переопределить повторно без ошибки.

---

## 🔹 Арифметические выражения
```
2 + 2         → 4
3 - 1         → 2
4 * 5         → 20
8 / 2         → 4
2 ^ 3         → 8
5 % 10       → 5
(2 + 3) * 4   → 20
"
Поддерживаемые операторы:

Оператор	Описание

+	Сложение
-	Вычитание
*	Умножение
/	Деление
^   Возведение в степень
%  Остаток от деления

```

---

##🔹 Функции

### Определение функции
```
funS <type> <name>(<params>): { return null! }

Пример:

funS i test(str: string): {
    retrun string!
}

```


##🔹 Условия

### Определение условий
```
if- <if> the
    ....
elif- <if> the
...
end--

Пример 

if- a >>> b the
    print-- "hello world"!
end--

```

---

## 🔹 Ошибки

Unknown variable -- Использование необъявленной переменной </br>
Invalid function -- Неизвестная функция </br>
Syntax error -- Ошибка в синтаксисе </br>
Duplicate variabl -- Повторное объявление переменной </br>
Wrong argument count -- Неверное число аргументов </br>

---

## 🧪 Мини-тест

Калькулятор на lo:

```
print-- "Добро пожаловать в калькулятор на lo!"!

loc num1 = int(0)!
loc num2 = int(0)!
loc op = str("")!

num1 = input-- i- "Введите первое число: "!
num2 = input-- i- "Введите второе число: "!

funS i sumC(i: numone, i: numtwo): {
    return numone + numtwo!
}

funS i minC(i: numone, i: numtwo): {
    return numone - numtwo!
}

funS i multC(i: numone, i: numtwo): {
    return numone * numtwo!
}

funS i delC(i: numone, i: numtwo): {
    return numone / numtwo!
}

funS i degC(i: numone, i: numtwo): {
    return numone ^ numtwo!
}

funS i perC(i: numone, i: numtwo): {
    return numone % numtwo!
}


    print-- "Сумма: "!
    print-- f-sumC(num1, num2)!

    print-- "Вычитание: "! 
    print-- f-minC(num1, num2)!

    print-- "Умножение: "!
    print-- f-multC(num1, num2)!

    print-- "Деление: "!
    print-- f-delC(num1, num2)!
    
    print-- "Возведение в степень: "!
    print-- f-degC(num1, num2)!
    
    print-- "Остаток от деления: "!
    print-- f-perC(num1, num2)!


print-- "Спасибо за использование калькулятора на lo!"!

```

---

## 🛠️ Сборка

```sh
sh build.sh
```
---

## 🔹 Запуск lo кода

```
./build/lomake script.lo
```

---

## 🧑‍💻 Авторы

@Android_xDev (telegram)
@TISERZ_DEVPROD (telegram)

---