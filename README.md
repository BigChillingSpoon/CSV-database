# CSV Database

## Podporované příkazy

-   **addrow `<v1>,<v2>,...,<vN>`** -- přidá nový řádek
-   **addcol `<nazev>` `<v1>,<v2>,...,<vN>`** -- přidá nový sloupec
-   **average `<sloupec>`** -- průměr hodnot
-   **min `<sloupec>`** -- minimum
-   **max `<sloupec>`** -- maximum
-   **sum `<sloupec>`** -- součet
-   **exit** -- uloží a ukončí

## Známé chybové hlášky

### Kritické chyby (ukončí program)

-   `CRITICAL ERROR: Input file cannot be opened`
-   `CRITICAL ERROR: Unable to save the database: File '%s' cannot be opened`
-   `CRITICAL ERROR: Output file path is not valid.`
-   `CRITICAL ERROR: Input file path is not valid.`
-   `CRITICAL ERROR: Invalid command line arguments.`
-   `CRITICAL ERROR: Output file path was not provided.`
-   `CRITICAL ERROR: Input file path was not provided.`
-   `CRITICAL ERROR: Memory allocation failed`
-   `CRITICAL ERROR: Row memory allocation failed`
-   `CRITICAL ERROR: Row values memory allocation failed`

### Běžné chyby

-   `ERROR: Input data is empty`
-   `ERROR: Command not found`
-   `ERROR: Wrong number of rows`
-   `ERROR: Wrong number of row values. Number of row values must match number of columns`
-   `ERROR: Column '%s' not found`
-   `ERROR: The table is empty. No row was found`
-   `ERROR: The table is empty. No column was found`

### Varování

-   `WARNING: File '%s' is empty`

## Kompilace

``` bash
mkdir build
cd build
cmake ..
make
```

## Spuštění

``` bash
./csv-database --input data.csv --output out.csv
```

## Parametry příkazové řádky

Program **musí** být spuštěn s těmito parametry:

### Povinné parametry

-   `--input <soubor.csv>`
    -   cesta k vstupnímu CSV souboru\
    -   **musí** končit příponou `.csv`
-   `--output <soubor.csv>`
    -   cesta k výstupnímu CSV souboru\
    -   **musí** končit `.csv`

### Co nesmí nastat

-   Parametry nesmí být zadány bez hodnot.
-   Nesmí být zadán neexistující nebo ne-CSV soubor.
-   Nesmí být zadán neznámý parametr.
-   Oba parametry **musí** být přítomné, jinak program skončí s
    kritickou chybou.

### Příklad správného spuštění

``` bash
./csv-database --input data.csv --output out.csv
```

### Příklady nesprávného spuštění

    ./csv-database --input data.txt        # špatná přípona
    ./csv-database --input data.csv        # chybí --output
    ./csv-database --output out.csv        # chybí --input
    ./csv-database --foo bar               # neznámý argument
