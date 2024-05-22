> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/uW28wxccPYtmCwIwo622CQ)

状态模式是一种行为型设计模式，它允许一个对象在其内部状态改变时改变它的行为。在状态模式中，对象的行为是依赖于它的状态的，并且当状态发生改变时，对象的行为也会相应地发生改变。这种模式通常适用于那些有多个状态，并且状态之间存在复杂转换逻辑的对象。通过将状态封装成独立的类，并将对状态的行为委托给当前状态对象，状态模式可以简化代码，提高可维护性，并避免使用大量的条件语句来控制对象的行为。

状态模式的一个常见应用是订单处理系统。在这个系统中，订单可以处于多个不同的状态，例如：待处理、已处理、已发货和已完成。每个状态对应着不同的操作和行为。

首先，我们定义一个订单状态的接口：

```
public interface IOrderState  
{  
    void Handle(Order order);  
}
```

然后，我们为每个状态实现具体的类：

```
public class PendingState : IOrderState  
{  
    public void Handle(Order order)  
    {  
        Console.WriteLine("Order is pending, preparing for processing.");  
        // 假设某些条件下订单被处理，这里简化为直接转换状态  
        order.SetState(new ProcessedState());  
    }  
}  
  
public class ProcessedState : IOrderState  
{  
    public void Handle(Order order)  
    {  
        Console.WriteLine("Order is processed, preparing for shipment.");  
        // 假设订单被发货，这里简化为直接转换状态  
        order.SetState(new ShippedState());  
    }  
}  
  
public class ShippedState : IOrderState  
{  
    public void Handle(Order order)  
    {  
        Console.WriteLine("Order has been shipped.");  
        // 订单发货后，可以设置为完成状态，或根据业务需求进行其他操作  
        order.SetState(new CompletedState());  
    }  
}  
  
public class CompletedState : IOrderState  
{  
    public void Handle(Order order)  
    {  
        Console.WriteLine("Order has been completed.");  
        // 在完成状态下，可能不再需要执行其他操作  
    }  
}
```

接下来，我们定义订单类，它包含一个当前状态对象，并提供设置状态和请求处理的方法：

```
public class Order  
{  
    private IOrderState _currentState;  
  
    public Order()  
    {  
        // 订单初始化时，通常设置为待处理状态  
        _currentState = new PendingState();  
    }  
  
    public void SetState(IOrderState state)  
    {  
        _currentState = state;  
    }  
  
    public void RequestHandling()  
    {  
        _currentState.Handle(this); // 根据当前状态处理订单  
    }  
}
```

最后，在主程序中，我们可以模拟订单的处理过程：

```
class Program  
{  
    static void Main(string[] args)  
    {  
        Order order = new Order();  
  
        // 模拟订单的处理过程  
        order.RequestHandling(); // 输出 "Order is pending, preparing for processing."  
        order.RequestHandling(); // 假设订单已被处理，输出 "Order is processed, preparing for shipment."  
        order.RequestHandling(); // 假设订单已发货，输出 "Order has been shipped."  
        order.RequestHandling(); // 订单完成，输出 "Order has been completed."  
  
        Console.ReadLine();  
    }  
}
```

在这个例子中，订单的状态随着处理过程而改变，每个状态都有自己的处理方式。当订单状态变化时，相关的行为也会自动变化。通过使用状态模式，我们可以将订单状态和行为分离，使得代码更加清晰和易于维护。同时，如果需要添加新的状态或修改现有状态的行为，我们只需要添加或修改相应的状态类，而不需要修改订单类或其他相关代码。