#include <stdio.h>

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

int main() {
	etudiant listeEtudiants[100] = {{12, "Boutaib", "Anass", "2001-03-06", 0, 17.75}};
	int totalEtudiant = 1;
	int choix;
	
	char departements[30][30] = {"Informatique"};
	int departmentsCount = 1;
	
	while (1) {
		menuPrincipal();
		scanf("%d", &choix);
		
		switch(choix) {
			case 1:
				totalEtudiant = ajouterEtudiant(listeEtudiants, totalEtudiant, departements, &departmentsCount);
				afficherEtudiants(listeEtudiants, totalEtudiant, departements);
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
	int choix, i, depTemp;
	
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
			printf("Numero unique:  ");
			scanf("%d", &tab[total].numero);
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
			
			printf("\nL'etudiant \"%s %s\" a ete ajoute\n", tab[total].prenom, tab[total].nom);
			return ++total;
		}
		if (choix == 2) {
			printf("\n");
			printf("------------------------------------------\n");
			printf("---   Ajouter des nouveaux etudiants   ---\n");
			printf("------------------------------------------\n");
			printf("\n");
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

//int modifierEtudiant() {
//	int nbrUnique;
//	
//	printf("\nVeuillez entrer le numero unique de l'etudiant a modidfier:  ");
//	scanf("%d", &nbrUnique);
//	
//	
//}
