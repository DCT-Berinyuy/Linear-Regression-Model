# Linear Regression Model - Refactored Version

## Overview
This is a refactored version of the original linear regression implementation. The refactoring focused on improving code structure, error handling, memory management, and maintainability.

## Key Improvements

### 1. Modular Design
- Created separate functions for different responsibilities:
  - `get_training_size()`: Handles input validation for training data size
  - `collect_training_points()`: Collects and validates training data
  - `get_hyperparameters()`: Gets epochs and learning rate from user
  - `train_step()`: Performs single gradient descent iteration
  - `train_model()`: Main training loop with logging and early stopping

### 2. Structured Data
- Introduced `TrainingData` structure to hold x/y coordinates and data size
- Introduced `LinearModel` structure to hold model parameters (gradient and intercept)

### 3. Memory Management
- Replaced Variable Length Arrays (VLAs) with dynamic memory allocation
- Proper memory allocation and deallocation functions (`initialize_training_data()` and `free_training_data()`)
- Error checking for memory allocation failures

### 4. Enhanced Error Handling
- Input validation for all user inputs
- Proper error messages to stderr
- Memory allocation failure checks
- Return proper exit codes (EXIT_SUCCESS/EXIT_FAILURE)

### 5. Improved Algorithm
- Batch gradient descent instead of updating parameters for each example
- Better calculation of average loss for logging
- More accurate convergence checking

### 6. Code Quality
- Clear variable names and consistent naming conventions
- Comprehensive comments and documentation
- Consistent formatting and structure
- Proper use of `const` where appropriate

### 7. Additional Features
- Better progress logging with average loss instead of total loss
- Fixed the early stopping condition to use average loss
- Improved user feedback messages

## Usage
The program works the same way as the original but with improved robustness and feedback:
1. Enter the number of training points
2. Enter each data point in x,y format
3. Specify number of training epochs (or use default)
4. Specify learning rate (or use default)
5. The program will train the model and output the resulting linear equation

## Files
- `main.c`: The refactored implementation
- `main`: The compiled executable (recompiled from the refactored code)

## Compilation
Compile with: `gcc -o main main.c -lm`
The `-lm` flag is needed for math functions.