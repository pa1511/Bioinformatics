# Bioinformatics
## Overlap phase in OLC (Overlap-Layout-Consensus) genome sequencing paradigm

The project for Bioinformatics course @ FER, University of Zagreb (2017/2018).

Course site: http://www.fer.unizg.hr/en/course/bio

## Instalation
After cloning the repositiory and positioning yourself in the repository directory, run the following command:
```
make
```

## Usage
To run the program, run the following command:
```
./BioInformatics [query-file] [target-file] [w] [k] [number-of-physical-units] > [output-file]
```
Example:
```
./BioInformatics ecoli_reference.fasta ecoli_reads.fasta 10 15 2 > ecoli_output.txt
```
