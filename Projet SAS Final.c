#include <stdio.h>
#include <string.h>

struct etudiant {
	int numero;
	char nom[30];
	char prenom[30];
	char dateNaissance[11];
	int departement;
	float note;
};

typedef struct etudiant etudiant;

void menuPrincipal();
int ajouterEtudiant(etudiant tab[], int total, char dep[][30], int *depCount);
void afficherEtudiants(etudiant tab[], int total, char dep[][30]);
void modifierEtudiant(etudiant tab[], int total, char dep[][30], int *depCount);
int supprimerEtudiant(etudiant tab[], int total);

int main() {
	etudiant listeEtudiants[100] = 
	{
		{1, "Boutaib", "Anass", "2001-03-06", 0, 17.75}, 
		{2, "Samih", "Mohamed", "2006-02-07", 1, 16}, 
		{3, "Chahbone", "Achraf", "1998-06-23", 0, 16.5}
	};
	int totalEtudiant = 3;
	int choix;
	
	char departements[30][30] = {"Informatique", "Mathematique"};
	int departmentsCount = 2;
	
	while (1) {
		menuPrincipal();
		scanf("%d", &choix);
		
		switch(choix) {
			case 1:
				totalEtudiant = ajouterEtudiant(listeEtudiants, totalEtudiant, departements, &departmentsCount);
				afficherEtudiants(listeEtudiants, totalEtudiant, departements);
				break;
			case 2:
				printf("\nVous voulez:\n");
				printf("1. Modifier les information d'un etudiant\n");
				printf("2. Supprimer un etudiant\n");
				printf("0. Annuler cet operation\n");
				printf("\n-->  ");
				scanf("%d", &choix);
				if (choix == 1) {
					modifierEtudiant(listeEtudiants, totalEtudiant, departements, &departmentsCount);
				} else if (choix == 2) {
					totalEtudiant = supprimerEtudiant(listeEtudiants, totalEtudiant);
					afficherEtudiants(listeEtudiants, totalEtudiant, departements);	
				} else {
					printf("\nL'operation a ete annuler\n");
				}
				
				
				break;
			case 0:
				printf("\nMerci pour l'utilisation de ce programme. Au revoir!\n");
				return;
			default: 
				printf("\nCe choix n'est pas valable\n");
		}
	}
	
	return 0;
}

void menuPrincipal() {
	printf("\n");
	printf("-----------------------------\n");
	printf("---   Le menu principal   ---\n");
	printf("-----------------------------\n");
	printf("\n");
	printf("1. Ajouter un etudiant\n");
	printf("2. Modifier ou supprimer un etudiant\n");
	printf("3. Afficher les details d'un etudiant\n");
	printf("4. Calculer la moyenne generale\n");
	printf("5. Statistiques\n");
	printf("6. Rechercher un etudiant\n");
	printf("7. Trier un etudiant\n");
	printf("\n-->  ");
}

void afficherEtudiants(etudiant tab[], int total, char dep[][30]) {
	int i;
	for (i = 0; i < total; i++) {
		printf("Numero unique:      %d\n", tab[i].numero);
		printf("Nom Complete:       %s %s\n", tab[i].prenom, tab[i].nom);
		printf("Date de naissance:  %s\n", tab[i].dateNaissance);
		printf("Departement:        %s\n", dep[tab[i].departement]);
		printf("Note:               %.2f\n", tab[i].note);
		printf("\n");
	}
}

int ajouterEtudiant(etudiant tab[], int total, char dep[][30], int *depCount) {
	int choix, j, i, depTemp, nbr;
	
	printf("\n");
	printf("-------------------\n");
	printf("---   L'ajout   ---\n");
	printf("-------------------\n");
	printf("\n");
	printf("1. Ajouter un etudiant\n");
	printf("2. Ajouter plusieurs etudiants\n");
	printf("0. Annuler\n");
	while (1) {
		
		printf("\n-->  ");
		
		scanf("%d", &choix);
		
		if (choix == 1) {
			printf("\n");
			printf("---------------------------------------\n");
			printf("---   Ajouter un nouveau etudiant   ---\n");
			printf("---------------------------------------\n");
			printf("\n");
			printf("Veuillez entrer les information de ce nouveau etudiant\n");
			if (total != 0) {
				tab[total].numero = tab[total - 1].numero + 1;	
			} else {
				tab[total].numero = 1;
			}
			printf("Nom:            ");
			scanf("%s", tab[total].nom);
			printf("Prenom:         ");
			scanf("%s", tab[total].prenom);
			printf("Date de naissance (yyyy-mm-dd):  ");
			scanf("%s", tab[total].dateNaissance);
			
			// Departement
			
			while (1) {
				
				printf("\nVeuillez selectionnez ou ajouter un nouveau departement:\n");
				for (i = 0; i < *depCount; i++) {
					printf("%d. %s\n", i + 1, dep[i]);
				}
				printf("0. Lier l'etudiant a un nouveau departement\n");
				printf("\n-->  ");
				scanf("%d", &depTemp);
				
				if (depTemp > 0 && depTemp <= *depCount) {
					tab[total].departement = depTemp - 1;
					break;
				} else if (depTemp == 0) {
					printf("Entrer le nom de ce nouveau departement:  ");
					scanf("%s", dep[*depCount]);
					tab[total].departement = *depCount;
					(*depCount)++;
					printf("\nLe nouveau departement a ete ajoute\n\n");
					break;
				} else {
					printf("\n### ( ! ) Veillez choisir un parmi les departement valable ou ajouter un nouveau ###\n");
				}
			}
			
			// Note Generale
			
			printf("Note generale:  ");
			scanf("%f", &tab[total].note);
			
			printf("\nL'etudiant \"%s %s\" a ete ajoute\n\n", tab[total].prenom, tab[total].nom);
			return ++total;
		}
		if (choix == 2) {
			printf("\n");
			printf("------------------------------------------\n");
			printf("---   Ajouter des nouveaux etudiants   ---\n");
			printf("------------------------------------------\n");
			printf("\n");
			
			printf("\nCombien d'etudiants vous voulez ajouter?  ");
			scanf("%d", &nbr);
			
			printf("\nVeuillez entrer les information des nouveaux etudiants\n\n");
			
			for (j = 0; j < nbr; j++) {
				printf("Nouveau etudiant #%d\n", j + 1);
				if (total != 0) {
					tab[total].numero = tab[total - 1].numero + 1;	
				} else {
					tab[total].numero = 1;
				}
				printf("Nom:            ");
				scanf("%s", tab[total].nom);
				printf("Prenom:         ");
				scanf("%s", tab[total].prenom);
				printf("Date de naissance (yyyy-mm-dd):  ");
				scanf("%s", tab[total].dateNaissance);
				
				// Departement
				
				while (1) {
					
					printf("\nVeuillez selectionnez ou ajouter un nouveau departement:\n");
					for (i = 0; i < *depCount; i++) {
						printf("%d. %s\n", i + 1, dep[i]);
					}
					printf("0. Lier l'etudiant a un nouveau departement\n");
					printf("\n-->  ");
					scanf("%d", &depTemp);
					
					if (depTemp > 0 && depTemp <= *depCount) {
						tab[total].departement = depTemp - 1;
						break;
					} else if (depTemp == 0) {
						printf("Entrer le nom de ce nouveau departement:  ");
						scanf("%s", dep[*depCount]);
						tab[total].departement = *depCount;
						(*depCount)++;
						printf("\nLe nouveau departement a ete ajoute\n\n");
						break;
					} else {
						printf("\n### ( ! ) Veillez choisir un parmi les departement valable ou ajouter un nouveau ###\n");
					}
				}
				
				// Note Generale
				
				printf("Note generale:  ");
				scanf("%f", &tab[total].note);
				
				printf("\nL'etudiant \"%s %s\" a ete ajoute\n\n", tab[total].prenom, tab[total].nom);
				total++;
			}
			return total;
		}
		if (choix == 0) {
			printf("\nL'operation a ete annuler\n");
			return;
		} else {
			printf("\nCe choix n'est pas valable\n");
		}
	}
}

void modifierEtudiant(etudiant tab[], int total, char dep[][30], int *depCount) {
	int nbrUnique, choix, depTemp, i;
	
	printf("\n");
	printf("--------------------------------\n");
	printf("---   Modifier un etudiant   ---\n");
	printf("--------------------------------\n");
	printf("\n");
	
	printf("Veuillez entrer le numero unique de l'etudiant a modidfier:  ");
	scanf("%d", &nbrUnique);
	
	int j = 0;
	
	while (j < total && nbrUnique != tab[j].numero) {
		j++;
	}
	
	if (j == total) {
		printf("\nCet etudiant ne se trouve pas\n");
		return;
	}
	
	printf("\nLes details de cet etudiant:\n");
	printf("Numero unique:      %d\n", tab[j].numero);
	printf("Nom Complete:       %s %s\n", tab[j].prenom, tab[j].nom);
	printf("Date de naissance:  %s\n", tab[j].dateNaissance);
	printf("Departement:        %s\n", dep[tab[j].departement]);
	printf("Note:               %.2f\n", tab[j].note);
	printf("\n\n");
	
	while (1) {
		printf("Modifier:\n");
		printf("1. Nom\n");
		printf("2. Prenom\n");	
		printf("3. Date de naissance\n");
		printf("4. Departement\n");
		printf("5. Note generale\n");
		printf("0. Annuler\n");
		printf("\n-->  ");
		scanf("%d", &choix);
		
		if (choix == 1) {
			printf("\nEntrer le nouveau nom:  ");
			scanf("%s", tab[j].nom);
			printf("\nLe nom d'etudiant du numero %d a ete modifier\n", tab[j].numero);
			break;
		} else if (choix == 2) {
			printf("\nEntrer le nouveau prenom:  ");
			scanf("%s", tab[j].prenom);
			printf("\nLe prenom d'etudiant du numero %d a ete modifier\n", tab[j].numero);
			break;
		} else if (choix == 3) {
			printf("\nEntrer la nouvelle date de naissance (yyyy-mm-dd):  ");
			scanf("%s", tab[j].dateNaissance);
			printf("\nLa date de naissance d'etudiant \"%s %s\" a ete modifier\n", tab[j].prenom, tab[j].nom);
			break;
		} else if (choix == 4) {
			while (1) {
				printf("\nVeuillez selectionnez ou ajouter un nouveau departement:\n");
				for (i = 0; i < *depCount; i++) {
					printf("%d. %s\n", i + 1, dep[i]);
				}
				printf("0. Lier l'etudiant a un nouveau departement\n");
				printf("\n-->  ");
				scanf("%d", &depTemp);
				
				if (depTemp > 0 && depTemp <= *depCount) {
					tab[j].departement = depTemp - 1;
					break;
				} else if (depTemp == 0) {
					printf("Entrer le nom de ce nouveau departement:  ");
					scanf("%s", dep[*depCount]);
					tab[j].departement = *depCount;
					(*depCount)++;
					printf("\nLe nouveau departement a ete ajoute\n\n");
					break;
				} else {
					printf("\n### ( ! ) Veillez choisir un parmi les departement valable ou ajouter un nouveau ###\n");
				}
			}
			printf("\nLe departement d'etudiant \"%s %s\" a ete modifier\n", tab[j].prenom, tab[j].nom);
			break;
		} else if (choix == 5) {
			printf("\nEntrer la nouvelle note generale:  ");
			scanf("%f", &tab[i].note);
			printf("\nLa note generale d'etudiant \"%s %s\" a ete modifier\n", tab[j].prenom, tab[j].nom);
			break;
		} else if (choix == 0) {
			printf("\nL'operation a ete annuler\n");
			return;
		} else {
			printf("\n### ( ! ) Ce choix n'est pas valables###\n");
		}
	}
	
	printf("\nLes nouveaux details de cet etudiant:\n");
	printf("Numero unique:      %d\n", tab[j].numero);
	printf("Nom Complete:       %s %s\n", tab[j].prenom, tab[j].nom);
	printf("Date de naissance:  %s\n", tab[j].dateNaissance);
	printf("Departement:        %s\n", dep[tab[j].departement]);
	printf("Note:               %.2f\n", tab[j].note);
	
}

int supprimerEtudiant(etudiant tab[], int total) {
	int nbrUnique;
	char fullName[61];
	
	printf("\n");
	printf("---------------------------------\n");
	printf("---   Supprimer un etudiant   ---\n");
	printf("---------------------------------\n");
	printf("\n");
	
	printf("Veuillez entrer le numero unique de l'etudiant a supprimer:  ");
	scanf("%d", &nbrUnique);
	
	int i = 0;
	
	while (i < total && tab[i].numero != nbrUnique) {
		i++;
	}
	
	if (i == nbrUnique) {
		printf("\nL'etudiant ne se trouve pas\n");
		return total;
	}
	
	strcpy(fullName, tab[i].prenom);
	strcat(fullName, " ");
	strcat(fullName, tab[i].nom);
	
	for (i = i; i < total - 1; i++) {
		tab[i] = tab[i + 1];
	}
	total--;
	
	printf("\nL'etudiant \"%s %s\" a ete modifier\n", fullName);
	
	return total;
}
