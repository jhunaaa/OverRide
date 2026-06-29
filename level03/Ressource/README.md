# CTF Level03 : Exploitation de `scanf` et décryptage XOR

## **Objectif**

Passer le niveau 03 en décryptant une chaîne de caractères via une opération **XOR**.

---

## **Analyse du binaire**

### **Fonctionnement du programme**

1. Le binaire `level03` utilise la fonction `scanf` pour lire une entrée utilisateur (un entier).
2. Cette entrée est transmise à la fonction `test()` **avec un deuxième argument fixe** : `322424845`.

---

### **Fonction `test()**`

- La fonction `test()` calcule **la différence absolue** entre l'entier saisi par l'utilisateur et la valeur hardcodée `322424845`.
- **Condition** : Si cette différence est **inférieure à 21**, la valeur est passée à la fonction `decrypt()`.

---

### **Fonction `decrypt()**`

- La fonction `decrypt()` prend un entier en paramètre et l'utilise pour **appliquer un XOR** sur chaque caractère de la chaîne hardcodée :
  ```
  "Q}|u`sfg~sf{}|a3"
  ```
- Le résultat de cette opération XOR est ensuite **comparé à la chaîne** :
  ```
  "Congratulations!"
  ```

---

## **Exploitation**

### **Découverte de la clé XOR**

1. On observe que pour obtenir la chaîne `"Congratulations!"`, chaque caractère de la chaîne hardcodée doit être **XORé avec une valeur constante**.
2. En analysant la différence entre les deux chaînes, on déduit que **la clé XOR est 18** (0x12 en hexadécimal).
  - Exemple :
    - `'Q' XOR 18 = 'C'`
    - `'}' XOR 18 = 'o'`
    - etc.

---

### **Calcul de l'entrée valide**

Pour que la fonction `decrypt()` soit appelée avec la bonne clé (18) :

- La différence entre l'entrée utilisateur et `322424845` doit être **18** (car `18 < 21`).
- On en déduit que l'entrée à fournir est :
  ```
  322424845 - 18 = 322424827
  ```

---

## **Solution**

Pour réussir le niveau, il suffit d'exécuter le binaire avec l'argument suivant :

```bash
./level03 322424827
```

---

## **Explication technique**


| Étape | Description                                                                |
| ----- | -------------------------------------------------------------------------- |
| 1     | `scanf` lit l'entrée utilisateur (un entier).                              |
| 2     | `test()` calcule la différence entre l'entrée et `322424845`.              |
| 3     | Si la différence est < 21, `decrypt()` est appelée.                        |
| 4     | `decrypt()` applique un XOR avec la différence sur la chaîne hardcodée.    |
| 5     | Le résultat est comparé à `"Congratulations!"`.                            |
| 6     | On déduit que la différence doit être **18** pour obtenir la bonne chaîne. |


---

## **Conclusion**

En fournissant l'entier `**322424827**` au binaire, on déclenche la bonne opération XOR et on obtient le message de succès : `**"Congratulations!"**`.
