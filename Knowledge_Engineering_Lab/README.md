# Complete KE(DataWarehouse - DataMining) lab Assignments from 3-1 semester

The input data is nothing mentioned is taken from text example from page 250 in `Data Mining Concepts and Techniques` by `Jaiwen Han & Kamber & Pei`, 3rd edition

## [Lab Assignment - 1](./Assignment_1)

    1. Consider given static transaction database.
    2. Consider random transactions.
    3. Items in transaction must be "characters"

## [Lab Assignment - 2](./Assignment_2)

    1. Brute Force approach to extract frequent itemsets Consider Transaction database given in assignment-1
    2. Min support= 2
    3. Min support =25% ,50%

## [Lab Assignment - 3](./Assignment_3)

    1. Candidate itemsets generation (all possible)
        i. Join step
        ii. Prune step
    2. Extract Frequent itemsets with sup>=minsup, consider minsup=2 from above question1. (use probability or proportional value as minimum support instead of integer)
    3. Implement 1,2 using random number generation based transactions and itemsets

## [Lab Assignment - 4](./Assignment_4)

    1. Implement any 3 missing values techniques considering 20 random values with 2 missing position
    2. Implement Binning techniques,  considering 20 random values and text book data
    3. Implement missing values using class labels

## [Lab Assignment - 5](./Assignment_5)

    1. Normalization Techniques (look into page-113) Create your own data values for 2 columns and implement all three normalization techniques.
    2. Generate Association Rules with minimum confidence 30% , 50%, 70%

## [Lab Assignment - 6](./Assignment_6)

    1. Implement Hash Based technique to extract frequent itemsets on Static Transaction Database for 2-length and 3-length itemsets with minimum support=3
        a. Consider hash function (x*10+y)%7 for length (x*10-y*5+z)%7
        b. Consider you own hash functions.
    2. Implement Partition Based Algorithm on Static Transaction Database with minimum support=35%

## [Lab Assignment - 7](./Assignment_7)

    Implement dynamic itemset counting (DIC) algorithm to extract frequent itemsets on textbook transaction database with minsup=35%(consider ceil value)

## [Lab Assignment - 8](./Assignment_8)

    Construct FP - Tree and extract frequent itemsets for textbook transaction database with minsupport=35%(consider ceil value)

## [Lab Assignment - 9](./Assignment_9)

    Construct decision tree for textbook dataset
    
    consider test samples:

      senior high yes fair
      youth high yes fair
      middle_aged low no excellent

    input: dataset file
    code file
    output screen shots with decision tree or all possible paths , information gain of each attribute in each step, predictions of test samples

## [Lab Assignment - 10](./Assignment_10)

    Implement Naive Bayes classification

    consider test samples:
      senior high yes fair
      youth high yes fair
      middle_aged low no excellent

## [Lab Assignment - 11](./Assignment_11)

    Implement k-means algorithm for clustering Consider random 25 points(2D) and form 3 clusters

    Input: DataPoints 
    output: clusters(cluster centers, sample-cluster) screenshots of output

    Implement OLAP operations on the 25 samples with atleast 3 attributes