/*
 * Jeu X — jeu de stratégie à deux joueurs dans le terminal.
 * Auteur : Ahmet BASBUNAR
 */

#include <stdio.h>
#include <stdlib.h>

// Définition des constantes pour des valeurs booléennes
#define VRAI 1
#define FAUX 0
#define TailleMax 101

// Fonction pour lire un entier ; vide la ligne si la saisie n'est pas un nombre
int lireEntier(int *n) {
    int res = scanf("%d", n);
    if (res == EOF) {
        printf("\nFin de saisie, arrêt du jeu.\n");
        exit(0);
    }
    if (res != 1) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
        *n = -1; // Valeur invalide pour forcer une nouvelle saisie
        return FAUX;
    }
    return VRAI;
}

// Fonction pour créer et initialiser la grille avec des zéros
void Creationtab(int nbl, int nbc, int grille[TailleMax][TailleMax]) {
    for (int i = 0; i < nbl; i++) {
        for (int j = 0; j < nbc; j++) {
            grille[i][j] = 0; // Initialisation de chaque cellule à 0
        }
    }
}

void afficherGrille(int nbl, int nbc, int grille[TailleMax][TailleMax]) {
    printf("    "); // Espace initial pour aligner les numéros des colonnes
    for (int j = 0; j < nbc; j++) {
        printf(" %2d ", j + 1); // Affiche les numéros des colonnes avec largeur fixe
    }
    printf("\n");

    for (int i = 0; i < nbl; i++) {
        printf("   "); // Espacement avant la bordure supérieure
        for (int j = 0; j < nbc; j++) {
            printf("+---"); // Bordure supérieure de chaque cellule
        }
        printf("+\n");

        printf("%2d ", i + 1); // Numéro de ligne avec alignement fixe
        for (int j = 0; j < nbc; j++) {
            printf("|"); // Bordure verticale de chaque cellule
            if (grille[i][j] > 0) {
                printf("\033[0;34m%2d \033[0m", grille[i][j]); // Bleu pour joueur A (aligné à 2 caractères)
            } else if (grille[i][j] < 0) {
                printf("\033[0;31m%2d \033[0m", grille[i][j]); // Rouge pour joueur B (aligné à 2 caractères)
            } else {
                printf(" 0 "); // Case vide avec espace pour alignement
            }
        }
        printf("|\n");
    }

    printf("   "); // Espacement avant la bordure inférieure
    for (int j = 0; j < nbc; j++) {
        printf("+---"); // Bordure inférieure de chaque cellule
    }
    printf("+\n");
}

// Fonction pour demander et valider le nombre de lignes et de colonnes
void demanderNombreLignesColonnes(int *lignes, int *colonnes) {
    do {
        printf("Entrez le nombre de lignes (impair, entre 3 et %d) : ", TailleMax);
        lireEntier(lignes);
        printf("Entrez le nombre de colonnes (impair, entre 3 et %d) : ", TailleMax);
        lireEntier(colonnes);

        // Vérifie que les dimensions sont impaires et entre 3 et TailleMax
        if ((*lignes >= 3 && *lignes <= TailleMax && *lignes % 2 != 0) &&
            (*colonnes >= 3 && *colonnes <= TailleMax && *colonnes % 2 != 0)) {
            break; // Les dimensions sont valides, on sort de la boucle
        }

        printf("Valeurs incorrectes. Les dimensions doivent être impaires et entre 3 et %d.\n", TailleMax);
    } while (1);
}

// Fonction pour calculer les scores autour de la case vide
void calculerScores(int nbl, int nbc, int grille[TailleMax][TailleMax], int *scoreA, int *scoreB) {
    int vide_i = -1, vide_j = -1;

    // Rechercher la case vide
    for (int i = 0; i < nbl; i++) {
        for (int j = 0; j < nbc; j++) {
            if (grille[i][j] == 0) {
                vide_i = i;
                vide_j = j;
                break;
            }
        }
    }

    *scoreA = 0;
    *scoreB = 0;

    // Calculer les scores autour de la case vide
    for (int i = vide_i - 1; i <= vide_i + 1; i++) {
        for (int j = vide_j - 1; j <= vide_j + 1; j++) {
            if (i >= 0 && i < nbl && j >= 0 && j < nbc && (i != vide_i || j != vide_j)) {
                if (grille[i][j] > 0) {
                    *scoreA += grille[i][j];
                } else if (grille[i][j] < 0) {
                    *scoreB += abs(grille[i][j]);
                }
            }
        }
    }
}

// Fonction principale
int main(void) {
    char nomA[20], nomB[20];
    int grille[TailleMax][TailleMax];
    int nbl, nbc, nbJetons;
    int l, c, saisieValide;
    int jeton; // Numéro des jetons pour chaque joueur
    int rejouer = VRAI;
    int scoreA, scoreB;
    int joueur = 1;

    // Message de bienvenue et demande des noms des joueurs
    printf("Bienvenue dans le jeu X\n");
    printf("Entrez le nom du joueur A : ");
    scanf("%19s", nomA);
    printf("Entrez le nom du joueur B : ");
    scanf("%19s", nomB);

    while (rejouer) {
        // Initialisation
        demanderNombreLignesColonnes(&nbl, &nbc);
        Creationtab(nbl, nbc, grille);
        afficherGrille(nbl, nbc, grille);
        nbJetons = (nbl * nbc - 1) / 2;
        jeton = 1;

        // Jeu principal
        while (jeton <= nbJetons) {
            printf("\nJoueur %s (Jeton %d)\n", (joueur == 1 ? nomA : nomB), jeton);
            do {
                printf("Entrez le numéro de la ligne (1 à %d) : ", nbl);
                lireEntier(&l);
                printf("Entrez le numéro de la colonne (1 à %d) : ", nbc);
                lireEntier(&c);
                l--; c--; // Ajustement pour l'indexation
                if (l >= 0 && l < nbl && c >= 0 && c < nbc && grille[l][c] == 0) {
                    grille[l][c] = (joueur == 1 ? jeton : -jeton);
                    saisieValide = VRAI;
                } else {
                    printf("Position invalide ou case déjà occupée. Réessayez.\n");
                    saisieValide = FAUX;
                }
            } while (!saisieValide);

            afficherGrille(nbl, nbc, grille);

            // Alterner les joueurs
            if (joueur == 1) {
                joueur = 2;
            } else {
                joueur = 1;
                jeton++;
            }
        }

        // Calcul des scores
        calculerScores(nbl, nbc, grille, &scoreA, &scoreB);
        printf("\nScore du joueur %s : %d\n", nomA, scoreA);
        printf("Score du joueur %s : %d\n", nomB, scoreB);

        // Afficher le gagnant
        if (scoreA < scoreB) {
            printf("Le gagnant est %s avec le score le plus bas : %d !\n", nomA, scoreA);
        } else if (scoreB < scoreA) {
            printf("Le gagnant est %s avec le score le plus bas : %d !\n", nomB, scoreB);
        } else {
            printf("Match nul !\n");
        }
        // Rejouer ?
        printf("\nVoulez-vous rejouer ? (1 : oui / 0 : non) : ");
        lireEntier(&rejouer);
        if (rejouer != 1) rejouer = FAUX;
    }

    return 0;
}
