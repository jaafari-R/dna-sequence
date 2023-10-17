

#ifndef DNA_SEQUENCE
#define DNA_SEQUENCE

#include <string>
#include <memory>
#include <vector>

/*  
    * This class is a representation of a DNA Sequence,
    * A DNA Sequence is a sequence of Nucleotides each 
     Nucleotide can have one of the following values: A, T, G, C.
    * The DNA Sequence is stored in the heap memory, and is deleted when the DNASequence
     destructor is called.
*/
class DNASequence {
public:
    /* Create an empty DNA Sequence. */
    DNASequence();

    /* 
        * Create a DNA Sequence that equals the values presented in the string.
        * If the DNA Sequence has a character other than 'a', 't', 'g', 'c', 'A', 'T', 'G', 'C'
        * the created sequence will be empty and an error message will be printed/output
    */
    DNASequence(const std::string &sequence);
    
    /* 
        * Create a DNA Sequence that equals the values presented in the c string.
        * If the size is not provided, the c string must end with a string termination character ('\0' or 0).
        * If the DNA Sequence has a character other than 'a', 't', 'g', 'c', 'A', 'T', 'G', 'C'.
        * The created sequence will be empty and an error message will be printed/output.
    */
    DNASequence(const char* sequence, const size_t size);
    
    DNASequence(const DNASequence &sequence);

    ~DNASequence();

    /* 
        * Creates and Returns the pair sequence
        * In a Pair Sequence, each Nucleutide is replaced with its pair:
            A is replaced with T
            T is replaced with A
            G is replaced with C
            C is replaced with G
    */
    DNASequence pairSequence();

    /*
        * Reverses the sequence in the range [start, end)
           'end' is not included, the length of the reversed value is 
           end - start.
        * The sequence is 0-indexed.
        * If only 'start' was given (end == -1) or 'end' was bigger than the sequence size,
           then the sequence is reversed from 'start' to the end of the sequence.
        * If 'start' was not set (start == 0), then the entire sequence is reversed.
        * If 'start was set to a value bigger or equal to the the sequence length, then nothing happens
    */
    void reverseSequence(size_t start = 0, size_t end = -1);

    /*
        * Returns a slice of the current DNASequence.
        * The slice starts at index 'start' and ends at index 'end', index 'end' is not included in the slice
        * The size of the slice is 'end' - 'start'.
        * if end is not specified, the slice is from 'start' to the end of the sequence.
        * if start is equalt to or bigger than end or the slice size, an empty sequence is returned 
    */
    DNASequence slice(size_t start = 0, size_t end = -1);

    /*
        * Returns true if the subsequence starting at index 'start_index' matches the passed subsequence
    */
    bool matchSubsequence(const std::string &subsequence, size_t start_index);
    bool matchSubsequence(const char* subsequence, size_t size, size_t start_index);
    bool matchSubsequence(const DNASequence &subsequence, size_t start_index);

    /*
        * Returns a vector containing the starting index of the first 'n' subsequences matching the passed subsequence
    */
    std::vector<size_t> findSubsequence(const std::string &subsequence, size_t n = -1);
    std::vector<size_t> findSubsequence(const char* subsequence, size_t size, size_t n = -1);
    std::vector<size_t> findSubsequence(const DNASequence &subsequence, size_t n = -1);

    /* 
        Returns the number of times a subsequence occured in a sequence
    */
    size_t countSubsequence(const std::string &subsequence);
    size_t countSubsequence(const char* subsequence, size_t size);
    size_t countSubsequence(const DNASequence &subsequence);

    /*
        * Returns True if the sequence contains the passed subsequence
    */
    bool hasSubsequence(const std::string &subsequence);
    bool hasSubsequence(const char* subsequence, size_t size);
    bool hasSubsequence(const DNASequence &subsequence);

    /*
        * Returns the starting index of the 'n'th occurance of the passed subsequence.
        * If the subsequence does not occure 'n' times, -1(max value for size_t) is returned
    */
    size_t findNthSubsequence(const std::string &subsequence, size_t n);
    size_t findNthSubsequence(const char* subsequence, size_t size, size_t n);
    size_t findNthSubsequence(const DNASequence &subsequence, size_t n);

    /* Operators */
    char operator[](size_t index) const;

    /* Getters */
    size_t getSize();
    std::string getSequenceStr();
    char* getSequenceCStr();

private:
    std::unique_ptr<char> m_sequence;
    size_t m_size;
};

#endif