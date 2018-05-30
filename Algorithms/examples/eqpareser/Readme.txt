Equation Evaluator Solution
By:         Habib Farahani
Date:       5/20/2018


                        STATEMENT OF WORK:
__________________________________________________________________________________________________
The following code package depicts a simple equation evaluator based on requirements presented
by Tesla engineering team as shown below:

    -   An equation is deﬁned by: <LHS> = <RHS> 
        • Each equation is speciﬁed on a separate line. 
        • <LHS> is the left-hand side of the equation and is always a variable name. 
        • A variable name is composed of letters from the alphabet ( for which isalpha(c) is true ). 
        • <RHS> is the right hand side of the equation and can be composed of: 
                • variables 
                • unsigned integers 
                • the + operator

    -   The program should take a ﬁlename as input. The ﬁle contains a set of equations, like:
                offset = 4 + random + 1 
                location = 1 + origin + offset 
                origin = 3 + 5 
                random = 2

    
    -   It should evaluate the set of equations and print the value of each variable. 
    -   The output should be sorted in ascending order by variable name. 
    -   If any variable doesn’t have a well deﬁned and unique solution, this indicates an error in input. 
        Print the exact contents of input ﬁle and exit. 
 

                        PROCEDURE
__________________________________________________________________________________________________
The followings are the steps required to build and deploy this package:   

    • Please extract the TeslaAsignment.zip in a local folder.
    • CD into eqparser folder where the Makefile is and simply type "make".
    • This package requires modern GNU compiler supporting C++11 extensions.
    • The resulting binary is called eval and can be invoked as:
        .\eval <name of input file>
  
    • Additionally, if you cd into jobSchedule folder and do a make and run ./schdeuler you should see
        the implementation of the phone interview coding session.


                        PACKAGE STRUCTURE
__________________________________________________________________________________________________
    
The followin section lists out the folder structure as:
./components
    ./components/Parameters	
        Constants.h                 // Definition for LiteralConstants object derived from EquationParameters
        Params.cpp                  // Implementation of EquationParameters object
        Params.h                    // Definition of EquationParameters object
        Variables.h                 // Definition for Variables object derived from EquationParameters
    ./components/Operators
        Add.cpp                     // Implementation for Add operator derived from Operators class
        Add.h                       // Definition for Add operator derived from Operators class
        Operators.h                 // Definition for Operators class.
        Subtract.cpp                // Implementation for Subtract operator derived from Operators class (not used only an example)
        Subtract.h                  // Definition for Subtract operator derived from Operators class
./evaluator 
    EquationEvaluator.cpp           // Implementation of evaluator (Signleton) object that evaluates all variables recursively
    EquationEvaluator.h             // Definition for the above object.
./parser
    EquationParser.cpp              // Implemenatation of the pasrer object that constructs the MAP for evaluator object.
    EquationParser.h                // This object will perform a non discriminatory verification of the equations input.
./
    main.cpp                        // The use cases for the above objects
    Makefile                        // Makefile to build the project
    testeq                          // Sample equation text file.


                            THEORY OF OPERATION
__________________________________________________________________________________________________
This package lays the foundation for an equation evaluator that only supports unsigned integers, variables of the same type
and add operators.  The way the objects are designed is that they can be extended to support additional operators, as well
as additional data types, such as signed short, signed integers, floating points, etc.  I intentionally did not use 
Templates (Template <TYPE>) to avoid the complexity and readability and instead used a polymorphic approach as shown below from
bottom to top:

    -   EquationParameter can be morphed into a LiteralConstant (which in turn can morph into other data types) or Variables.

    -   Operators can morph into Add, or Subtract, but they can be extended to support Mult, div, and other operators which
        require more constraints.

    -   Equation is the main container that can be composed of a series of EquationParameters and Operators.  Each object shall
        be stored in a separate <vector> object.  For an equation to be valid:
        • It should have at least on parameter element in its <RHS>
        • Its left hand side should be a variable.
        • The Parameters and Operators should be lined up one at a time.
        • It should end with a parameter.
        • Number of operators should always be 1 minus number of parameters.
         
    -   EquationParser is an object that takes an input file and:
        • Parses the file line by line
        • Split each line into an array of strings comprised of Variables, 
             and operators (only addition for now), and constant literals (only unsigned int for now)
        • For each line an Equation object will be constructed and each parameter (variables or constants)
             and each operator will be added to the equation object.
        • Each equation object will contain a VECTOR of operators and a VECTOR of parameters.
        • In the end each equation object then is inserted into a MAP of equations where the LHS will be the 
             key element of the MAP.
        • Once all Equations are inserted in the MAP, the routine verifies that:
                 a.  There are no unresolved externals.  Which means that all variables have a UNIQUE solution.
                 b.  There are circular dependency between variables as it needs algebraic methods to solve
                     solve such dependencies.  This capability can be added with current architecture.

    -   EquationEvaluator is an object that creates an equation <map> that will be populated by EquationParser object.
        Upon successfull parsing, the evaluation starts:
        •  For each equation in the MAP starting from beginning.
        •  Get the first parameter and if it is a variable, recuse into evaluate.
        •  If the first param is a literal constant the start a loop for the number of operators.
        •  Store the results in the associated Equation object so it well become (Evaluated = true)
        •  Store the evaluated results in currentValue.
        •  For each operator in the Equation get the next param (keep in mind the each equation is already verified by parser object)
        •  Follow the same steps as step 2 and store the results in newValue.
        •  Now with currentValue and newValue in hand, perform the operation and store the results in currentValue.
        •  Keep repeating steps 6 and on ward for each operator.
        •  Once we are done with the operators, then currentValue holds the value that needs to be assigned to the
            Equation object at hand which is also represented by a variable (its LHS) used a key into its MAP entry.
        •  Once all equations are exhausted. we are done!

    I still would like to profile the performance with large and more complex input files.
    Though the data strauctures and the overall routine is quite fast and efficient, there are two major in efficiencies:

        1.  All data is stored in strings.  Which means all arithmetic will convert from string to appropriate types
            and after the correct operation is performed, they will be converted back to string.

        2.  The set of equations are stored in a <map> stl object.  The advantage of using this data structure is that all equations
            are sorted based on their referencing variable, and therefore we do not need to sort them.  But for larger sets, and
            during recursive calls to evaluate, search can become quite time consuming with main O(n) operations.  This could have 
            been prevented by using a <unsorted_set> which internally uses a hash algorithm.  Therefore each search will boil down to O(1)
            time complexity.
    
                           FURTHER ENHANCEMENTS
__________________________________________________________________________________________________
    I think it would be worth wile to at least look into:
        -   The effects of using Templates so that data types can be preserved with having to be maintained
            in string form which the current implementation does.

        -   Adding support for dynamic variables generation that can allow complex equations to be broken
            down into simpler ones.  This can be added as a complementary package to EquationParser.

        -   Once the above is implemented adding support for Mult, Div operators would be trivial.

        -   Adding supports for math functions when above is implemented.

        -   Adding support for (, ), [, ], {, }, and etc.

        -   Usage of <unsorted_set> for a faster lookup instead of <map> of Equations 



                            REFRENECES
__________________________________________________________________________________________________
I have looked in several code repos to get an idea but found most:
    - Very limited in functionality.
    - Not very efficient algorithms.
    - Immature data structures and algorithms.
    - Not extendable for future development without a major rewrite.
    - regex usage.
    - lambda function (being compiled but not used)

My main source of reference was Stack Overflow mainly for ideas on usages of STL.







