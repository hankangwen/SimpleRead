> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s?__biz=Mzg2MjUzMzcyOA==&mid=2247484127&idx=1&sn=0353a566bc7bec28d5866ba4cdcd96cf&chksm=ce0723d0f970aac68b201c55b770c9c2f72c53fc78b025bbc02c5ca4ebce3102272d48dbf46b&scene=178&cur_album_id=3242994881078460418#rd)

**C# 中 == 和 Equals 的区别是什么**

**值类型：**

对于值类型来说 == 和 Equals 的作用是一致的，都是比较它们的值是否相等

**引用类型：**

== 比较的是它们的引用是否相等；默认情况下是比较引用类型的引用，但如果重写它来自定义对象的比较方式，就是比较 “值”。

c# 的许多引用类型都已经重写了 Equals 方法，以便根据对象的内容进行比较。一些常见的引用类型包括：

字符串类型（string）：字符串类型已经重写了 Equals 方法，使其比较字符串的值而不是引用。

集合类型（如 List、Dictionary 等）。

```c#
// String.cs
public static bool operator ==(string a, string b) => string.Equals(a, b);
在String中， == 和 Equals 是一样的，都是比较字符串的值。
string a = "EqualsExample";
string b = "EqualsExample";
Debug.Log($"{a == b} {a.Equals(b)}");//True True

//List
List<string> strList1 = new List<string>(3);
List<string> strList2 = new List<string>();
strList1.Add("1");
strList2.Add("1");
strList1.Add("2");
strList2.Add("2");
strList1.Add("3");
strList2.Add("3");
bool bA = strList1 == strList2;
bool bB = strList1.SequenceEqual(strList2);
Debug.Log($"{bA} {bB}");// False True  
Debug.Log($"{strList1 == strList2} {strList1.Equals(strList2)}");// False False

//Dictionary
Dictionary<int, string> aDict = new Dictionary<int, string>(3);
Dictionary<int, string> bDict = new Dictionary<int, string>();
aDict.Add(1, "1");
bDict.Add(1, "1");
aDict.Add(2, "2");
bDict.Add(2, "2");
aDict.Add(3, "3");
bDict.Add(3, "3");
bool bA = aDict == bDict;
bool bB = aDict.Equals(bDict);
bool bC = aDict.SequenceEqual(bDict);
Debug.Log($"{bA} {bB} {bC}");//False False True
```



如果我们自定义一个类，并且没有重写 Equals 方法，那么该类的对象在使用 Equals 方法进行比较时，默认情况下会比较它们的引用，而不是内容。

**重写 Equals**

在 .NET 中，一些常见的引用类型并且已经重写 Equals 方法包括：

字符串类型（string）：字符串类型已经重写了 Equals 方法，使其比较字符串的值而不是引用。

集合类型（如 List、Dictionary 等）：集合类型通常会重写 Equals 方法，以便比较集合的元素是否相等。例如，List 类型会比较列表中的每个元素是否相等。

自定义类：如果我们自定义了一个类，可以通过重写 Equals 方法来定义对象的比较方式。这样可以根据对象的属性或字段来判断它们是否相等。

例如，假设我们有一个自定义的 Person 类：

```c#
public class Person
{
    public string Name { get; set; }
    public int Age { get; set; }

    public override bool Equals(object obj)
    {
        if (obj == null || GetType() != obj.GetType())
            return false;

        Person otherPerson = (Person)obj;
        return Name == otherPerson.Name && Age == otherPerson.Age;
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(Name, Age);
    }
}
```

在上述代码中，我们重写了 Person 类的 Equals 方法和 GetHashCode 方法来实现根据 Name 和 Age 属性来比较两个 Person 对象的相等性。

注意：

重写 GetHashCode() 方法是为了保证对象在哈希表等数据结构中能够正常工作。在使用哈希表、字典等集合类型时，这些集合类型会使用对象的哈希码来确定存储位置或进行快速查找操作。

哈希码是一个整数值，用于表示对象的内容。同样内容的对象应该具有相同的哈希码，这样才能确保它们被正确地放置在哈希表中的同一个桶中。因此，当我们重写 Equals 方法时，也应该同时重写 GetHashCode() 方法，以确保一致性。

在示例代码中，我们重写了 Person 类的 Equals 方法，并在 GetHashCode() 方法中使用了 HashCode.Combine() 方法来生成哈希码。Hashcode.Combine() 方法接受多个值作为参数，并根据这些值来计算哈希码。在本例中，我们使用了 Name 和 Age 属性作为生成哈希码的依据。HashCode.Combine(Name, Age); 意思是是基于 Name 和 Age 这两个值来生成一个组合的哈希码。

重写 GetHashCode() 方法的目的是让两个相等的对象具有相同的哈希码，以确保它们能够被正确地放置在哈希表中的同一个桶中，并在需要时能够高效地进行查找和比较操作。

请注意，根据 .NET 框架的规定，如果两个对象通过 Equals 方法判断为相等，则它们的哈希码必须相等。但是，两个哈希码相等的对象并不一定相等。因此，正确地重写 Equals 和 GetHashCode 方法是保证对象比较和哈希表性能的关键。