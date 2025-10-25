# Инфа о FixedLo

FixedLo — работа над ошибками реализации языка Lo, автор его может мёрджить, когда я посчитаю его готовым (то есть запрошу мёрдж)

Мёрдж был запрошен: 
1 раз

---

# 📘 LO Language — Документация по синтаксису

LO — минималистичный язык с поддержкой переменных, функций и выражений. Ниже представлен полный синтаксис.

---

## 🔹 Переменные

### Объявление

``` lo

loc <name> = <type>(<value>)!

Примеры:

print-- "hello, lo!"!

loc x = int(5)!
loc y = str("hello, world!")!
loc flag = bool(true)!
loc nums = arr(1, 2, 3, 4, 5)!

print-- y!
```
> Переменные нельзя переопределить повторно без ошибки. Тип данных выбирается при объявлении и сохраняется.

---

---

## 🔹 Типы данных

```
Тип	Описание	Пример

int	64-битное целое число (long long)	loc x = int(12345)!
str	строка в кавычках	loc s = str("text")!
bool	логическое значение (true / false)	loc b = bool(true)!
arr	список значений (массив)	loc nums = arr(1, 2, 3)!
```


---

## 🔸 int — 64-битные целые

int — 64-битное целое (long long)

Диапазон: -9,223,372,036,854,775,808 … 9,223,372,036,854,775,807

Поддерживаются все стандартные арифметические операции: +, -, *, /, %, ^


> Примечание: при операциях, которые выходят за пределы 64-бита, результат может быть ограничен LLONG_MAX или LLONG_MIN. В будущих версиях планируется поддержка BigInt для произвольной длины чисел.

---

## 🔸 str — строчные значения

Пример:

``` lo
loc text = str("hello, lo!")

print-- text!
```

---

## 🔸 bool — логические значения

Поддерживает два состояния:

``` lo
loc a = bool(true)!
loc b = bool(false)!
```

Может использоваться в условиях:

``` lo
if- a === b the
    print-- "равны"!
end--
```

---

## 🔸 arr — массивы (экспериментальная возможность)

``` lo
loc nums = arr(10, 20, 30, 40)!

print-- nums!  # => [10, 20, 30, 40]
```

> В текущей версии массив — это просто список значений, без индексации и циклов.
В будущем появится доступ по индексу и перебор.


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

## 🔹 Функции

### Определение функции
``` lo
funS <type> <name>(<params>): { return null! }

Пример:

funS i test(str: string): {
    retrun string!
}

```


## 🔹 Условия

### Определение условий
``` lo
if- <if> the
    ....
elif- <if> the
...
end--

Пример 

if- a >>> b the
    print-- "hello world"!
end--

> Операторы сравнения:
>> — больше, << — меньше, === — равно
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

``` lo
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

``` sh
sh build.sh
```
---

## 🚀 Запуск lo кода

``` sh
./build/lomake script.lo
```

---

## 🧑‍💻 Авторы

@Android_xDev (telegram)
@TISERZ_DEVPROD (telegram)

---
