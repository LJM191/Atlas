# Installation et utilisation

1. Ouvrir l'onglet **Actions** du dépôt GitHub.
2. Ouvrir le dernier workflow **Build NumWorks Ultimate** terminé avec succès.
3. Télécharger l'artefact **NumWorks-Ultimate-NWA** et extraire le fichier `app.nwa`.
4. Importer le fichier avec l'uploader officiel : https://my.numworks.com/apps

La calculatrice doit être compatible avec les applications externes EADK. Les applications externes sont masquées en mode examen. Un RESET peut les supprimer.

## Commandes de navigation

- Flèches haut/bas : déplacer la sélection.
- OK : ouvrir une catégorie ou une formule.
- BACK : revenir à l'écran précédent.

## Contenu actuel

La première version contient 21 rappels répartis entre électricité, chimie, ondes/énergie, mathématiques et mécanique. C'est un formulaire de consultation : les calculs numériques et le calcul symbolique ne sont pas encore implémentés.

## Dépannage

Si la compilation échoue, ouvrir le workflow puis le job **build** et consulter les logs de l'étape en erreur. Ne pas renommer un autre fichier en `.nwa` : seul le fichier généré par le linker est installable.
