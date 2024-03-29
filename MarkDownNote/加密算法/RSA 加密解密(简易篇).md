## 非对称加密之RSA加密和解密的讲解

 RSA公钥加密算法是1977年由Ron Rivest、Adi Shamirh和LenAdleman在（美国麻省理工学院）开发的。RSA取名来自开发他们三者的名字。RSA是目前最有影响力的公钥加密算法，它能够抵抗到目前为止已知的所有密码攻击，已被ISO推荐为公钥数据加密标准；RSA算法基于一个十分简单的数论事实：将两个大素数相乘十分容易，但是想要对其乘积进行因式分解却极其困难，因此可以将乘积公开作为加密密钥；RSA算法是第一个能同时用于加密和数字签名的算法，也易于理解和操作。

  RSA算法是被研究得最广泛的公钥算法，从提出到现在已近二十年，经历了各种攻击的考验，逐渐为人们所接受，被普遍认为是目前最优秀的公钥方案之一。RSA的安全性依赖于大数的因子分解，但并没有从理论上证明破译RSA的难度与大数分解难度等价，即RSA的重大缺陷是无法从理论上把握它的保密性能如何，而且密码学界多数人士倾向于因子分解不是NPC问题。





  RSA的缺点主要有：

  1）产生密钥很麻烦，受到素数产生技术的限制，因而难以做到一次一密。

  2）分组长度太大，为保证安全性，n至少也要600bits以上，导致运算代价很高，尤其是速度较慢（较对称密码算法慢几个数量级），且随着大数分解技术的发展，这个长度还在增加，不利于数据格式的标准化。目前，SET(Secure Electronic Transaction)协议中要求CA采用2048bits长的密钥，其它实体使用1024比特的密钥。

  3）RSA密钥长度随着保密级别提高，增加很快。

  下表列出了对同一安全级别所对应的密钥长度：

| 保密级别 | 对称密钥长度（bit） | RSA密钥长度（bit） | ECC密钥长度（bit） | 保密年限 |
| -------- | ------------------- | ------------------ | ------------------ | -------- |
| 80       | 80                  | 1024               | 160                | 2010     |
| 112      | 112                 | 2048               | 224                | 2030     |
| 128      | 128                 | 3072               | 256                | 2040     |
| 192      | 192                 | 7680               | 384                | 2080     |
| 256      | 256                 | 15360              | 512                | 2120     |

  RSA算法是一种非对称密码算法，所谓非对称，就是指该算法需要一对密钥，使用其中一个加密，则需要用另一个才能解密。

  RSA的算法涉及三个参数n、e1、e2：

  1）n是两个大质数p、q的积，n的二进制表示时所占用的位数，就是所谓的密钥长度。

  2）e1和e2是一对相关的值，e1可以任意取，但要求e1与(p-1)*(q-1)互质，再选择e2，要求(e2*e1)mod((p-1)*(q-1))=1。

  3）(n及e1)、(n及e2)就是密钥对。

  RSA加解密的算法完全相同，设A为明文，B为密文，则：A=B^e1 mod n；B=A^e2 mod n；

  e1和e2可以互换使用，即：A=B^e2 mod n；B=A^e1 mod n；

![img](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2022/08/12_9_36_42_1227623-20200102143843773-1145201632.png)

```

```

