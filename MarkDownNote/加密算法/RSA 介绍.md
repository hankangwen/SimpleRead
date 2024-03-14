> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/chengqiuming/article/details/82725137?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522165935471116781818734125%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=165935471116781818734125&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-2-82725137-null-null.142^v37^pc_rank_34&utm_term=RSA&spm=1018.2226.3001.4187)

##### **一 什么是 RSA**

[RSA](https://so.csdn.net/so/search?q=RSA&spm=1001.2101.3001.7020) 是一种公钥密码算法，它的名字由三位开发者，即 Ron Rivest、Adi Shamir 和 Leonard Adleman 的姓氏的首字母组成的。

RSA 被用于[公钥](https://so.csdn.net/so/search?q=%E5%85%AC%E9%92%A5&spm=1001.2101.3001.7020)密码和数字签名。

1983 年，RSA 公司为 RSA 算法在美国取得了专利，但现在该专利已经过期。

质数：只能由数字1和数字本身相乘得到的数。 a = 1 x a ，5 = 1 x 5, 13 = 1 x 13

##### **二 RSA 加密**

在 RSA 中，明文、[密钥](https://so.csdn.net/so/search?q=%E5%AF%86%E9%92%A5&spm=1001.2101.3001.7020)和密文都是数字。RSA 的加密过程可以用下面的公式来表达。

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2022/08/1_20_45_31_20180916154825652.png)

RSA 的密文是对代表了`明文的数字的 E 次方求 mod N 的结果`。换句话说，就是`将明文做 E 次乘方，然后将其结果除以 N 求余数，这个余数就是密文`。

加密公式中出现了两个数——E 和 N，到底都是什么数呢？RSA 的加密是求明文的 E 次方 mod N，因此只要知道 E 和 N 这两个数，任何人都可以完成加密的运算。所以说，E 和 N 是 RSA 加密的密钥，也就是说，`E 和 N 的组合就是公钥`。

不过，E 和 N 并不是随便什么数都可以的，它们是经过严密计算得出的。其中 E 是加密（Encryption）的首字母，N 是数字（Number）首字母。

有一个很容易引起误解的地方——E 和 N 这两个数并不是密钥对（公钥和私钥的密钥对）。E 和 N 两个数才组成一个公钥，因此我们一般会写出 “公钥是（E，N）” 或者 “公钥是{E，N}” 这样的形式，将 E 和 N 用括号括起来。

##### **三 RSA 解密**

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2022/08/1_20_45_36_1_20_45_12_20180916155256423.png)

该公式表示对`密文的数字的 D 次方求 mod N 就可以得到明文`。换句话说，`将密文自己做 D 次乘法，再对其结果除以 N 求余数，这个余数就是明文`。

这里使用的数字 N 和加密时使用的数字 N 是相同的。数 D 和数 N 组成起来就是 RSA 的解密密钥，因此 D 和 N 的组合就是私钥。只有知道 D 和 N 两个数的人才能够完成解密的运算。由于 N 是公钥的一部分，是公开的，因此单独将 D 称为私钥也是可以的。

`在 RSA 中，加密和解密的形式是相同的。加密是求 “E 次方的 modN”，而解密则是求 “D 次方的 modN”。`

当然，D 也并不是随便什么数都可以的，作为解密密钥的 D，和数字 E 有着相当紧密的联系。否则，用 E 加密的结果可以用 D 来解密这样的机制是无法实现的。

D 是解密（Decryption）的首字母，N 是数字（Number）的首字母。

##### **四 RSA 加密和解密小结**

![](https://img-blog.csdn.net/20180916155436675?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NoZW5ncWl1bWluZw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

![](https://img-blog.csdn.net/20180916155449615?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NoZW5ncWl1bWluZw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

##### **五 加密解密图解**

![image-20220802095337491](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2022/08/2_9_53_37_image-20220802095337491.png)

##### 六 公钥和私钥的制作

![image-20220802095404558](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2022/08/2_9_54_4_image-20220802095404558.png)

##### 七 李永乐老师讲RSA

![image-20220802141417341](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2022/08/2_14_14_17_image-20220802141417341.png)
