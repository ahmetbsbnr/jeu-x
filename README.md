# Jeu X

Un jeu de stratégie à deux joueurs dans le terminal, écrit en C.

## Règles
Deux joueurs (bleu / rouge) posent à tour de rôle leurs jetons numérotés de 1 à n sur un plateau de L × C cases (L et C impairs, ≥ 3), avec n = (L × C − 1) / 2. Les jetons se posent dans l'ordre croissant : bleu 1, rouge 1, bleu 2, rouge 2, etc.

Quand tous les jetons sont posés, il reste une seule case libre : on additionne les jetons de chaque couleur qui l'entourent (8 cases voisines). **La plus petite somme gagne** (égalité = match nul).

Exemple sur un plateau 3 × 5 : la somme bleue autour de la case libre vaut 14, la rouge 18 → le joueur bleu gagne.

## Compiler et lancer
```bash
gcc -Wall -o jeu_x jeu_x.c
./jeu_x
```
Fonctionne sous Linux et macOS (affichage couleur via les codes ANSI du terminal).

## Déroulement
1. Saisir le nom des deux joueurs.
2. Choisir la taille du plateau (lignes et colonnes impaires, de 3 à 101).
3. Chaque joueur indique la ligne puis la colonne où poser son jeton ; le plateau est réaffiché après chaque coup.
4. En fin de partie, les scores et le gagnant s'affichent, puis on peut rejouer.

## Auteur
Ahmet BASBUNAR
