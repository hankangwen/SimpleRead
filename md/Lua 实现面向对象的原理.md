> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/SWmAoNheN-GSZfkv5_iKLQ)

    Lua 并没有内建的面向对象系统，但我们可以使用其表和元表的特性来实现对象、类以及继承等面向对象编程的功能。

   Lua 的对象基本上就是一个表（table）。表在 Lua 中，是实现泛型数据结构的主要方式。在 Lua 中，表有两种用法：数组或是 hash。所有的键都是唯一的，并且可以是任何类型，除了 nil，包括函数和表。

    **_1. 创建一个对象_**：对象由表表示，并通过表来访问其数据和方法。

```
local person = {}
person.name = "bob"
person.age = 30
person.say_hello = function()
  print("hello, " .. person.name)
end

person.say_hello()  -- 输出："hello, bob"
```

    _**2. 创建一个类**_：Lua 面向对象系统的基础是 “原型” 的概念。我们可以将类理解为原型。Lua 中的类更像是一个模板：创建一个新对象时可以基于这个模板获得相同的属性和行为。

```
local Person = {name = "unknown", age = 0}

function Person:new(o)
  -- 使用 : Operator曾预设把self作为第一个参数传入function，此时一个table作为self传入
  o = o or {}    -- 新建表，并默认值为空表
  setmetatable(o, self)   -- self 就是 Person这个“类”
  self.__index = self  -- 访问nil值，可以取得父类的相关属性或方法
  return o
end

function Person:hello()
  print("hello, " .. self.name)
end

local bob = Person:new({name = "bob", age = 30})  

bob:hello()  -- 输出："hello, bob"
```

‍  

_**3. 实现继承**_：Lua 的继承是通过元表实现的。实际上是当访问一个表的元素时，如果该元素为空（nil），那么就转去访问该表元表的 __index 元方法。这样，只需要通过将父类设置为子类的元表，那么当访问子类的方法或变量为 nil 时，就可以返回父类相应的方法或变量。

    对于以上例子，如果我们需要一个 Child 类继承自 Person 类，就可以这样做：

```
local Child = Person:new() -- 在Person基础上新建表
Child = Person:new({age=10}) -- 直接链式赋值亦可
bob = Child:new({name = "bob"})
bob:hello()  -- 输出："hello, bob"
```

    在这里，Child 类会从 Person 类那里 “继承” 来 `hello` 方法。可以看到，Lua 中的面向对象编程更接近于原型编程，使用表和元表来实现面向对象中我们熟悉的对象、类和继承功能。然而这种实现面向对象编程的特性，提供了极大的灵活性，使 Lua 能轻松应用于各种复杂的编程环境中