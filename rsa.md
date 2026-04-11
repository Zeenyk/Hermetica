I’ll add a concise demonstration of Euler’s theorem into both the Italian and English versions, integrating it into the section on Euler’s theorem.

---

# RSA Algorithm: Mathematical Foundations, Operation, and Security

## 1. Mathematical Foundations

### 1.1 Modular Arithmetic and the Ring \(\mathbb{Z}_n\)

Modular arithmetic is the environment in which RSA operates. We work with the set  

\[
\mathbb{Z}_n = \{0,1,2,\dots,n-1\}
\]  

endowed with two **binary operations**: addition and multiplication performed **modulo \(n\)** (i.e., the result is the remainder upon division by \(n\)).

A **binary operation** on a set is a rule that assigns to every ordered pair \((a,b)\) of elements of the set a unique third element belonging to the same set. In symbols: \( * : R \times R \to R \).

The structure \((\mathbb{Z}_n, +, \cdot)\) forms a **commutative unital ring**. A **ring** is a set equipped with two binary operations, usually called addition (\(+\)) and multiplication (\(\cdot\)), satisfying:

1. **Additive abelian group:**  
   - Closure: \(a+b \in R\).  
   - Associativity: \((a+b)+c = a+(b+c)\).  
   - Identity: there exists \(0\in R\) such that \(a+0=a\).  
   - Inverse: for every \(a\) there exists \(-a\) such that \(a+(-a)=0\).  
   - Commutativity: \(a+b = b+a\).

2. **Multiplicative semigroup:**  
   - Closure: \(a\cdot b \in R\).  
   - Associativity: \((a\cdot b)\cdot c = a\cdot (b\cdot c)\).

3. **Distributive laws:**  
   \(a\cdot(b+c) = a\cdot b + a\cdot c\) and \((a+b)\cdot c = a\cdot c + b\cdot c\).

If multiplication is commutative, the ring is **commutative**; if there exists a multiplicative identity (denoted \(1\) such that \(1\cdot a = a\cdot 1 = a\)), the ring is **unital**. \(\mathbb{Z}_n\) is a commutative unital ring.

Among the elements of \(\mathbb{Z}_n\), those that possess a **multiplicative inverse** (i.e., an \(x\) with \(a\cdot x \equiv 1 \pmod n\)) are exactly those coprime to \(n\). This set is denoted \(\mathbb{Z}_n^*\) and forms a **multiplicative group**. Its size is given by Euler’s totient function \(\varphi(n)\).

### 1.2 Euler’s Totient Function \(\varphi(n)\)

\(\varphi(n)\) counts the integers between \(1\) and \(n\) that are coprime to \(n\).

- If \(p\) is prime: \(\varphi(p)=p-1\).
- If \(n = p\cdot q\) with \(p,q\) distinct primes: \(\varphi(n) = (p-1)(q-1)\).

### 1.3 Euler’s Theorem (and Fermat’s Little Theorem)

**Euler’s Theorem:** If \(\gcd(a,n)=1\), then  

\[
a^{\varphi(n)} \equiv 1 \pmod n.
\]

*Demonstration:*  
Let \(\mathbb{Z}_n^* = \{r_1, r_2, \dots, r_{\varphi(n)}\}\) be the set of residues modulo \(n\) that are coprime to \(n\). Since \(\gcd(a,n)=1\), multiplying each \(r_i\) by \(a\) (mod \(n\)) yields another residue coprime to \(n\). Moreover, if \(a r_i \equiv a r_j \pmod n\), then multiplying by \(a^{-1}\) (which exists modulo \(n\) because \(\gcd(a,n)=1\)) gives \(r_i \equiv r_j\). Hence the set \(\{a r_1 \bmod n, a r_2 \bmod n, \dots, a r_{\varphi(n)} \bmod n\}\) is exactly \(\mathbb{Z}_n^*\) in some order. Taking the product of all elements in \(\mathbb{Z}_n^*\) in two ways:

\[
\prod_{i=1}^{\varphi(n)} (a r_i) \equiv \prod_{i=1}^{\varphi(n)} r_i \pmod n.
\]

The left side is \(a^{\varphi(n)} \prod_{i=1}^{\varphi(n)} r_i\). Since each \(r_i\) is coprime to \(n\), the product \(\prod r_i\) is also coprime to \(n\) and therefore invertible modulo \(n\). Cancelling it from both sides yields \(a^{\varphi(n)} \equiv 1 \pmod n\).

**Fermat’s Little Theorem (special case):** If \(p\) is prime and \(p \nmid a\), then \(a^{p-1} \equiv 1 \pmod p\).

### 1.4 Extended Euclidean Algorithm and Modular Inverse

The **extended Euclidean algorithm** takes two integers \(a,b\) with \(\gcd(a,b)=1\) and finds integers \(x,y\) such that  

\[
ax + by = 1.
\]  

Then \(ax \equiv 1 \pmod b\), so \(x\) is the modular inverse of \(a\) modulo \(b\). This is used to compute the private exponent \(d\) in RSA.

### 1.5 Chinese Remainder Theorem (CRT)

If \(n = n_1 n_2 \cdots n_k\) with the moduli pairwise coprime, the system of congruences  

\[
\begin{cases}
x \equiv a_1 \pmod{n_1}\\
x \equiv a_2 \pmod{n_2}\\
\vdots\\
x \equiv a_k \pmod{n_k}
\end{cases}
\]  

has a unique solution modulo \(n\). In RSA, \(n=pq\) and CRT is used both in the correctness proof (for messages not coprime to \(n\)) and to speed up decryption.

---

## 2. The RSA Algorithm

RSA is an **asymmetric** cryptosystem: each user has a **public key** for encryption and a **private key** for decryption.

### 2.1 Key Generation

1. **Choose two distinct large primes** \(p\) and \(q\) (e.g., 1024 bits each for a 2048‑bit key). Primality is tested with probabilistic algorithms (Miller–Rabin).
2. **Compute** \(n = p \cdot q\). This modulus \(n\) is public.
3. **Compute** \(\varphi(n) = (p-1)(q-1)\). This value is kept secret.
4. **Choose a public exponent** \(e\) such that  
   \(1 < e < \varphi(n)\) and \(\gcd(e, \varphi(n)) = 1\).  
   For efficiency, \(e = 65537 = 2^{16}+1\) (a Fermat prime with only two 1‑bits) is commonly used.
5. **Compute the private exponent** \(d\) as the modular inverse of \(e\) modulo \(\varphi(n)\):  
   \[
   d \equiv e^{-1} \pmod{\varphi(n)}.
   \]  
   This is done using the extended Euclidean algorithm.
6. **Securely erase** \(p\), \(q\), and \(\varphi(n)\) from memory.

**Public key:** \((n, e)\)  
**Private key:** \((n, d)\)

### 2.2 Encryption

To send a secret message \(m\) (converted to an integer with \(0 \le m < n\)) to the owner of public key \((n,e)\):

\[
c = m^{\,e} \bmod n
\]

Exponentiation is performed using the **square‑and‑multiply** algorithm in \(O(\log e)\) modular multiplications.

### 2.3 Decryption

The recipient, possessing the private key \((n,d)\), recovers the message by computing:

\[
m = c^{\,d} \bmod n
\]

### 2.4 Proof of Correctness

By construction, \(e d = 1 + k\varphi(n)\) for some integer \(k \ge 1\). We must show \(m^{e d} \equiv m \pmod n\) for every \(m\).

**Case 1:** \(\gcd(m,n)=1\).  
By Euler’s theorem, \(m^{\varphi(n)} \equiv 1 \pmod n\). Then  

\[
m^{e d} = m^{1 + k\varphi(n)} = m \cdot (m^{\varphi(n)})^k \equiv m \pmod n.
\]

**Case 2:** \(\gcd(m,n) \neq 1\).  
Since \(n = pq\) with distinct primes, \(\gcd(m,n) \neq 1\) implies \(m\) is a multiple of \(p\) or \(q\) (but not both, otherwise \(m\) would be a multiple of \(n\) and, because \(0\le m<n\), we would have \(m=0\), a trivial case). Suppose \(p \mid m\) and \(q \nmid m\) (the other case is symmetric).

- Modulo \(p\): \(m \equiv 0 \Rightarrow m^{e d} \equiv 0 \equiv m \pmod p\).
- Modulo \(q\): \(\gcd(m,q)=1\). By Euler’s theorem modulo \(q\), \(m^{\varphi(q)} \equiv 1 \pmod q\). Since \(\varphi(n) = (p-1)(q-1) = \varphi(p)\varphi(q)\), we have  

\[
m^{e d} = m^{1 + k\varphi(p)\varphi(q)} = m \cdot (m^{\varphi(q)})^{k\varphi(p)} \equiv m \pmod q.
\]

Now we have \(m^{e d} \equiv m \pmod p\) and \(m^{e d} \equiv m \pmod q\). Because \(p\) and \(q\) are coprime, the **Chinese Remainder Theorem** implies the congruence holds modulo \(pq = n\):

\[
m^{e d} \equiv m \pmod n.
\]

### 2.5 Faster Decryption Using CRT

Decryption can be sped up by performing exponentiations modulo \(p\) and \(q\) separately. Precompute:

\[
d_p = d \bmod (p-1),\quad d_q = d \bmod (q-1),\quad q_{\text{inv}} = q^{-1} \bmod p.
\]

Then for a ciphertext \(c\):

\[
m_p = c^{d_p} \bmod p,\qquad m_q = c^{d_q} \bmod q,
\]
\[
m = m_q + q \cdot \bigl((m_p - m_q) \cdot q_{\text{inv}} \bmod p\bigr).
\]

Because the exponents and moduli are roughly half the size of \(n\), this method is significantly faster.

---

## 3. Numerical Example (Small Numbers)

1. **Choose primes:** \(p = 61\), \(q = 53\).
2. \(n = 61 \cdot 53 = 3233\).
3. \(\varphi(n) = (61-1)(53-1) = 60 \cdot 52 = 3120\).
4. Choose \(e = 17\) (coprime to 3120).
5. Compute \(d\) with the extended Euclidean algorithm:  
   \(3120 = 17 \cdot 183 + 9\)  
   \(17 = 9 \cdot 1 + 8\)  
   \(9 = 8 \cdot 1 + 1\)  
   \(8 = 1 \cdot 8 + 0\)  
   Back‑substitute: \(1 = 9 - 8 = 9 - (17-9) = 2\cdot 9 - 17 = 2(3120-17\cdot 183) - 17 = 2\cdot 3120 - 367\cdot 17\).  
   Hence \(-367 \equiv 3120-367 = 2753 \pmod{3120}\), so \(d = 2753\).
6. **Encrypt** \(m = 123\):  
   \(c = 123^{17} \bmod 3233\). Using square‑and‑multiply yields \(c = 855\).
7. **Decrypt** \(c = 855\):  
   \(m = 855^{2753} \bmod 3233 = 123\).

---

## 4. Security and Known Attacks

RSA’s security rests on the **difficulty of factoring** \(n = pq\). If an attacker can factor \(n\), they can compute \(\varphi(n)\) and recover \(d\) from the public key.

- **Factoring attack:** The best general‑purpose algorithm is the **General Number Field Sieve (GNFS)**. For 2048‑bit keys, factoring is considered infeasible with current technology.
- **Small \(e\):** If \(e\) is very small and no padding is used, a message with \(m^e < n\) can be recovered by taking the \(e\)-th root. This is prevented by using **padding** (OAEP, PKCS#1 v1.5).
- **Small \(d\):** If \(d\) is too small compared to \(n\), attacks like Wiener’s or Boneh–Durfee can recover \(d\). Therefore \(d\) is chosen to be of similar size as \(n\).
- **Side‑channel attacks:** Timing, power consumption, or electromagnetic leaks can expose the private key. Countermeasures include constant‑time exponentiation and **blinding** (multiplying \(c\) by a random value before decryption and compensating later).
- **Padding attacks:** OAEP (Optimal Asymmetric Encryption Padding) is provably secure in the random oracle model and is recommended for encryption.

---

## 5. Practical Recommendations

- **Key length:**  
  - 1024 bits: deprecated (factored by well‑resourced adversaries).  
  - 2048 bits: minimum recommended today.  
  - 3072/4096 bits: for long‑term security (beyond 2030).
- **Prime generation:** Primes must be random and independent. Avoid \(p\) and \(q\) that are too close (Fermat factorization) and ensure \(p-1, q-1\) have large prime factors (to resist Pollard’s \(p-1\) attack).
- **Exponent \(e\):** \(e = 65537\) is standard for efficiency and security.
- **Padding:** Never encrypt raw numeric messages; always use a secure padding scheme like RSA‑OAEP for encryption and RSA‑PSS for signatures.

---

## 6. RSA for Digital Signatures

RSA can also be used for **digital signatures**:

- The signer computes \(s = m^d \bmod n\), where \(m\) is a properly padded hash of the message.
- The verifier checks that \(s^e \bmod n\) equals the padded hash.

The security relies on the difficulty of computing \(e\)-th roots without knowledge of \(d\).

---

## Conclusion

RSA is a cornerstone of public‑key cryptography. Its mathematical correctness follows from Euler’s theorem and the Chinese remainder theorem, while its security is based on the hardness of integer factorization. Understanding the underlying algebraic structure—in particular the ring \(\mathbb{Z}_n\) and the multiplicative group \(\mathbb{Z}_n^*\)—is essential for grasping why the algorithm works and for implementing it securely.

---

# Traduzione in italiano (con la dimostrazione di Eulero integrata)

## 1. Basi matematiche

### 1.1 Aritmetica modulare e l’anello \(\mathbb{Z}_n\)

L’aritmetica modulare si svolge nell’insieme  

\[
\mathbb{Z}_n = \{0,1,2,\dots,n-1\}
\]  

dotato di due **operazioni binarie**: addizione e moltiplicazione eseguite **modulo \(n\)** (cioè si prende il resto della divisione per \(n\)).

Un’**operazione binaria** su un insieme è una regola che associa a ogni coppia ordinata \((a,b)\) di elementi dell’insieme un unico terzo elemento appartenente allo stesso insieme. In simboli: \( * : R \times R \to R \).

La struttura \((\mathbb{Z}_n, +, \cdot)\) è un **anello commutativo unitario**. Un **anello** è un insieme dotato di due operazioni binarie, solitamente chiamate addizione (\(+\)) e moltiplicazione (\(\cdot\)), che soddisfano:

1. **Gruppo abeliano rispetto all’addizione:**  
   - Chiusura: \(a+b \in R\).  
   - Associatività: \((a+b)+c = a+(b+c)\).  
   - Elemento neutro: esiste \(0\in R\) tale che \(a+0=a\).  
   - Inverso additivo: per ogni \(a\) esiste \(-a\) con \(a+(-a)=0\).  
   - Commutatività: \(a+b = b+a\).

2. **Semigruppo rispetto alla moltiplicazione:**  
   - Chiusura: \(a\cdot b \in R\).  
   - Associatività: \((a\cdot b)\cdot c = a\cdot (b\cdot c)\).

3. **Proprietà distributiva:**  
   \(a\cdot(b+c) = a\cdot b + a\cdot c\) e \((a+b)\cdot c = a\cdot c + b\cdot c\).

Se la moltiplicazione è commutativa, l’anello si dice **commutativo**; se esiste un elemento neutro per la moltiplicazione (indicato con \(1\) tale che \(1\cdot a = a\cdot 1 = a\)), l’anello si dice **unitario**. \(\mathbb{Z}_n\) è un anello commutativo unitario.

Tra gli elementi di \(\mathbb{Z}_n\), quelli che possiedono un **inverso moltiplicativo** (cioè una \(x\) tale che \(a\cdot x \equiv 1 \pmod n\)) sono esattamente i numeri coprimi con \(n\). Questo insieme si denota \(\mathbb{Z}_n^*\) e forma un **gruppo moltiplicativo**. La sua cardinalità è data dalla funzione \(\varphi(n)\) di Eulero.

### 1.2 Funzione \(\varphi\) di Eulero

\(\varphi(n)\) conta gli interi compresi tra \(1\) e \(n\) che sono coprimi con \(n\).

- Se \(p\) è primo: \(\varphi(p)=p-1\).
- Se \(n = p\cdot q\) con \(p,q\) primi distinti: \(\varphi(n) = (p-1)(q-1)\).

### 1.3 Teorema di Eulero (e Piccolo Teorema di Fermat)

**Teorema di Eulero:** Se \(\gcd(a,n)=1\), allora  

\[
a^{\varphi(n)} \equiv 1 \pmod n.
\]

*Dimostrazione:*  
Sia \(\mathbb{Z}_n^* = \{r_1, r_2, \dots, r_{\varphi(n)}\}\) l’insieme dei residui modulo \(n\) coprimi con \(n\). Poiché \(\gcd(a,n)=1\), moltiplicando ogni \(r_i\) per \(a\) (mod \(n\)) si ottiene ancora un residuo coprimo con \(n\). Inoltre, se \(a r_i \equiv a r_j \pmod n\), moltiplicando per l’inverso \(a^{-1}\) (che esiste perché \(\gcd(a,n)=1\)) si ottiene \(r_i \equiv r_j\). Dunque l’insieme \(\{a r_1 \bmod n, a r_2 \bmod n, \dots, a r_{\varphi(n)} \bmod n\}\) è esattamente \(\mathbb{Z}_n^*\) in un qualche ordine. Prendendo il prodotto di tutti gli elementi di \(\mathbb{Z}_n^*\) in due modi:

\[
\prod_{i=1}^{\varphi(n)} (a r_i) \equiv \prod_{i=1}^{\varphi(n)} r_i \pmod n.
\]

Il membro sinistro è \(a^{\varphi(n)} \prod_{i=1}^{\varphi(n)} r_i\). Poiché ogni \(r_i\) è coprimo con \(n\), anche il prodotto \(\prod r_i\) è coprimo con \(n\) e quindi invertibile modulo \(n\). Cancellandolo da entrambi i lati si ottiene \(a^{\varphi(n)} \equiv 1 \pmod n\).

**Piccolo Teorema di Fermat (caso particolare):** Se \(p\) è primo e \(p \nmid a\), allora \(a^{p-1} \equiv 1 \pmod p\).

### 1.4 Algoritmo Euclideo Esteso e inverso modulare

L’**algoritmo euclideo esteso** prende due interi \(a,b\) con \(\gcd(a,b)=1\) e trova interi \(x,y\) tali che  

\[
ax + by = 1.
\]  

Allora \(ax \equiv 1 \pmod b\), quindi \(x\) è l’inverso modulare di \(a\) modulo \(b\). Questo viene usato per calcolare l’esponente privato \(d\) in RSA.

### 1.5 Teorema cinese del resto (CRT)

Se \(n = n_1 n_2 \cdots n_k\) con i moduli a due a due coprimi, il sistema di congruenze  

\[
\begin{cases}
x \equiv a_1 \pmod{n_1}\\
x \equiv a_2 \pmod{n_2}\\
\vdots\\
x \equiv a_k \pmod{n_k}
\end{cases}
\]  

ha una soluzione unica modulo \(n\). In RSA, \(n=pq\) e il CRT viene usato sia nella dimostrazione di correttezza (per i messaggi non coprimi con \(n\)) sia per velocizzare la decrittografia.

---

## 2. L’algoritmo RSA

RSA è un crittosistema **asimmetrico**: ogni utente possiede una **chiave pubblica** per cifrare e una **chiave privata** per decifrare.

### 2.1 Generazione delle chiavi

1. **Scegliere due numeri primi distinti e grandi** \(p\) e \(q\) (es. 1024 bit ciascuno per una chiave da 2048 bit). La primalità viene verificata con algoritmi probabilistici (Miller–Rabin).
2. **Calcolare** \(n = p \cdot q\). Questo modulo \(n\) è pubblico.
3. **Calcolare** \(\varphi(n) = (p-1)(q-1)\). Questo valore rimane segreto.
4. **Scegliere un esponente pubblico** \(e\) tale che  
   \(1 < e < \varphi(n)\) e \(\gcd(e, \varphi(n)) = 1\).  
   Per efficienza si usa spesso \(e = 65537 = 2^{16}+1\) (un primo di Fermat con solo due bit a 1).
5. **Calcolare l’esponente privato** \(d\) come inverso modulare di \(e\) modulo \(\varphi(n)\):  
   \[
   d \equiv e^{-1} \pmod{\varphi(n)}.
   \]  
   Si ottiene con l’algoritmo euclideo esteso.
6. **Cancellare in modo sicuro** \(p\), \(q\) e \(\varphi(n)\) dalla memoria.

**Chiave pubblica:** \((n, e)\)  
**Chiave privata:** \((n, d)\)

### 2.2 Crittografia

Per inviare un messaggio segreto \(m\) (convertito in numero intero con \(0 \le m < n\)) al possessore della chiave pubblica \((n,e)\):

\[
c = m^{\,e} \bmod n
\]

L’elevamento a potenza viene eseguito con l’algoritmo **square‑and‑multiply** in \(O(\log e)\) moltiplicazioni modulari.

### 2.3 Decrittografia

Il destinatario, in possesso della chiave privata \((n,d)\), recupera il messaggio calcolando:

\[
m = c^{\,d} \bmod n
\]

### 2.4 Dimostrazione di correttezza

Per costruzione, \(e d = 1 + k\varphi(n)\) per qualche intero \(k \ge 1\). Dobbiamo mostrare che \(m^{e d} \equiv m \pmod n\) per ogni \(m\).

**Caso 1:** \(\gcd(m,n)=1\).  
Per il teorema di Eulero, \(m^{\varphi(n)} \equiv 1 \pmod n\). Allora  

\[
m^{e d} = m^{1 + k\varphi(n)} = m \cdot (m^{\varphi(n)})^k \equiv m \pmod n.
\]

**Caso 2:** \(\gcd(m,n) \neq 1\).  
Poiché \(n = pq\) con primi distinti, \(\gcd(m,n) \neq 1\) implica che \(m\) è multiplo di \(p\) o di \(q\) (ma non di entrambi, altrimenti \(m\) sarebbe multiplo di \(n\) e, dato \(0\le m<n\), si avrebbe \(m=0\), caso banale). Supponiamo \(p \mid m\) e \(q \nmid m\) (l’altro caso è simmetrico).

- Modulo \(p\): \(m \equiv 0 \Rightarrow m^{e d} \equiv 0 \equiv m \pmod p\).
- Modulo \(q\): \(\gcd(m,q)=1\). Per il teorema di Eulero modulo \(q\), \(m^{\varphi(q)} \equiv 1 \pmod q\). Poiché \(\varphi(n) = (p-1)(q-1) = \varphi(p)\varphi(q)\), abbiamo  

\[
m^{e d} = m^{1 + k\varphi(p)\varphi(q)} = m \cdot (m^{\varphi(q)})^{k\varphi(p)} \equiv m \pmod q.
\]

Ora abbiamo \(m^{e d} \equiv m \pmod p\) e \(m^{e d} \equiv m \pmod q\). Poiché \(p\) e \(q\) sono coprimi, il **teorema cinese del resto** implica che la congruenza vale modulo \(pq = n\):

\[
m^{e d} \equiv m \pmod n.
\]

### 2.5 Decrittografia veloce con il CRT

La decrittografia può essere accelerata eseguendo le esponenziazioni separatamente modulo \(p\) e modulo \(q\). Si precalcolano:

\[
d_p = d \bmod (p-1),\quad d_q = d \bmod (q-1),\quad q_{\text{inv}} = q^{-1} \bmod p.
\]

Quindi per un cifrato \(c\):

\[
m_p = c^{d_p} \bmod p,\qquad m_q = c^{d_q} \bmod q,
\]
\[
m = m_q + q \cdot \bigl((m_p - m_q) \cdot q_{\text{inv}} \bmod p\bigr).
\]

Poiché gli esponenti e i moduli hanno circa la metà dei bit di \(n\), questo metodo è molto più veloce.

---

## 3. Esempio numerico (numeri piccoli)

1. **Scelta dei primi:** \(p = 61\), \(q = 53\).
2. \(n = 61 \cdot 53 = 3233\).
3. \(\varphi(n) = (61-1)(53-1) = 60 \cdot 52 = 3120\).
4. Scegliamo \(e = 17\) (coprimo con 3120).
5. Calcolo di \(d\) con l’algoritmo euclideo esteso:  
   \(3120 = 17 \cdot 183 + 9\)  
   \(17 = 9 \cdot 1 + 8\)  
   \(9 = 8 \cdot 1 + 1\)  
   \(8 = 1 \cdot 8 + 0\)  
   Sostituendo all’indietro: \(1 = 9 - 8 = 9 - (17-9) = 2\cdot 9 - 17 = 2(3120-17\cdot 183) - 17 = 2\cdot 3120 - 367\cdot 17\).  
   Quindi \(-367 \equiv 3120-367 = 2753 \pmod{3120}\), perciò \(d = 2753\).
6. **Crittografia** di \(m = 123\):  
   \(c = 123^{17} \bmod 3233\). Usando square‑and‑multiply si ottiene \(c = 855\).
7. **Decrittografia** di \(c = 855\):  
   \(m = 855^{2753} \bmod 3233 = 123\).

---

## 4. Sicurezza e attacchi noti

La sicurezza di RSA si basa sulla **difficoltà di fattorizzare** \(n = pq\). Se un attaccante riesce a fattorizzare \(n\), può calcolare \(\varphi(n)\) e quindi ricavare \(d\) dalla chiave pubblica.

- **Attacco di fattorizzazione:** Il miglior algoritmo generale è il *General Number Field Sieve (GNFS)*. Per chiavi a 2048 bit, la fattorizzazione è considerata impossibile con le tecnologie attuali.
- **\(e\) piccolo:** Se \(e\) è molto piccolo e non si usa padding, un messaggio con \(m^e < n\) può essere recuperato estraendo la radice \(e\)-esima. Per prevenirlo si utilizza un **padding** (OAEP, PKCS#1 v1.5).
- **\(d\) piccolo:** Se \(d\) è troppo piccolo rispetto a \(n\), attacchi come Wiener o Boneh–Durfee possono recuperare \(d\). Per questo \(d\) viene scelto con dimensione simile a \(n\).
- **Attacchi laterali:** Tempi di esecuzione, consumo di potenza o emissioni elettromagnetiche possono rivelare la chiave privata. Contromisure: esponenziazione a tempo costante e **blinding** (moltiplicare \(c\) per un valore casuale prima della decrittografia e compensare dopo).
- **Attacchi al padding:** OAEP (Optimal Asymmetric Encryption Padding) è dimostrato sicuro nel modello dell’oracolo casuale ed è raccomandato per la crittografia.

---

## 5. Raccomandazioni pratiche

- **Lunghezza della chiave:**  
  - 1024 bit: deprecato (fattorizzabile da avversari con risorse adeguate).  
  - 2048 bit: minimo raccomandato oggi.  
  - 3072/4096 bit: per sicurezza a lungo termine (oltre il 2030).
- **Generazione dei primi:** I primi devono essere casuali e indipendenti. Evitare \(p\) e \(q\) troppo vicini (fattorizzazione di Fermat) e assicurarsi che \(p-1\) e \(q-1\) abbiano fattori primi grandi (per resistere all’attacco di Pollard \(p-1\)).
- **Esponente \(e\):** \(e = 65537\) è lo standard per efficienza e sicurezza.
- **Padding:** Non cifrare mai messaggi numerici grezzi; usare sempre uno schema di padding sicuro come RSA‑OAEP per la crittografia e RSA‑PSS per le firme.

---

## 6. RSA per firme digitali

RSA può essere usato anche per **firme digitali**:

- Il firmatario calcola \(s = m^d \bmod n\), dove \(m\) è l’hash del messaggio con opportuno padding.
- Il verificatore controlla che \(s^e \bmod n\) corrisponda all’hash con padding.

La sicurezza si basa sulla difficoltà di calcolare radici \(e\)-esime senza conoscere \(d\).

---

## Conclusione

RSA è un pilastro della crittografia asimmetrica. La sua correttezza matematica discende dal teorema di Eulero e dal teorema cinese del resto, mentre la sicurezza si fonda sulla difficoltà della fattorizzazione. Comprendere la struttura algebrica sottostante – in particolare l’anello \(\mathbb{Z}_n\) e il gruppo moltiplicativo \(\mathbb{Z}_n^*\) – è essenziale per capire perché l’algoritmo funziona e per implementarlo in modo sicuro.
