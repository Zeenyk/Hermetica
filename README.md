# Hermetica

## **Crittografia RSA**
Per questo progetto useremo **l'algoritmo** di crittografia asimmetrico **RSA** (Rivest - Shamir - Adleman).
Consiste nell'uso di due chiavi, una pubblica $(n, e)$ e una privata $(n, d)$.
Il funzionamente è descritto in seguito.

**Descrizione dell'algoritmo**
Siano $p, q$ due numeri primi.
Calcoliamo $n$ come prodotto di $p, q$

$$
n = p \cdot q
$$

e $\phi(n)$ come prodotto di $p-1$ e $q-1$

$$
\phi(n) = (p-1) \cdot (q-1)
$$

**N.B.:** la dimensione di $n$ deve essere strettamente minore di quella del messaggio $m$.

Successivamente troviamo un numero $e$ che deve essere coprimo con $\phi(n)$.

Infine ricaviamo il numer $d$, tale che:

$$
d \cdot e \equiv 1 \mod{\phi(n)}
$$

Per calcolarlo possiamo usare l'algoritmo di Eclide esteso, che permette di trovare l'inverso modulare di un numero.

**Algoritmo di euclide esteso**
Siano $a, b$ due numeri che costituiscono la seguente relazione:

$$
a \cdot b \equiv 1 \mod{n}
$$

e siano $a, n$ noti.
Affinché esista un b tale che la conguenza sia soddisfatta, $a$ e $m$ devono essere coprimi, ovvero $GCD(a, m)=1$.
Se la condizione è soddisfatta troviamo b applicando l'algoritmo:

**1. Dividi** $n$ per $a$ per ottenere un certo quoziente $q$ e il resto $r$.

$$
n = a \cdot q + r
$$

**2. Ripeti** il processo sostituendo $n$ con $a$, e $a$ con $r$, fino a quando non trovi $r = 0$.
**3. Riscrivi** l'ultima relazionme trovata in cui $r \not= 0$. Poi puoi sostituire la $a$ con il resto $r$ dell'equazione precedente dal momento che $a$ è definita estattamente in questo modo.
Iteri queste sostituzioni fino a ritrovare i numeri di partenza $a, n$ e riscrivi la relazione in modo takle da avere una combinazione lineare di $a$ e $n$
$$
a \cdot x + n \cdot y = 1
$$
A questo punto avremo che $x$ è l'inverso modulare di $a \mod{n}$.


**Crittografia e decrittografia**
Ottenuti i valori $n, e, d$, possiamo scrivere la chiave pubblica e privata:
La **chiave pubblica** è costituita dalla coppia **$(n, e)$**.
La **chiave privata** è costituita dalla coppia **$(n, d)$**.

Dato il messaggio $m$, il messaggio criptato $c$ è:
$$
c = m^e \mod{n}
$$
Per decriptarlo:
$$
m = c^d \mod{n}
$$