 Linear Regression Tutorial: Explaining main.c Line by Line


Linear regression is a statistical method to model the relationship between variables by fitting a straight line (or plane) to data, predicting a dependent variable (outcome) from one or more independent variables (predictors) using the least squares method to find the best-fit line that minimizes prediction errors, used widely for forecasting and understanding trends in fields from economics to machine learning

  Code Breakdown

  1. Header Files

   1 #include <math.h>
   2 #include <stdio.h>
   - stdio.h: For input/output functions like printf and scanf
   - math.h: For mathematical functions like fabs (absolute value)

  2. Main Function Declaration

   1 int main() {
   - Entry point of the program

  3. Variable Declarations

   1 size_t i, train_size = 1;
   - i: Loop counter
   - train_size: Number of training data points (initialized to 1 as a default)

  4. Welcome Messages and Input Collection

   1 printf("Welcome to linear regressor!\n");
   2 printf("Let's start training the model\n");
   3 printf("What number of graph points do you have?\n> ");
   4 scanf("%zd", &train_size);
   - Display welcome message
   - Prompt user for number of data points
   - Store the input in train_size

  5. Dynamic Data Storage

   1 double x[train_size];
   2 double y[train_size];
   - Declare arrays to store x and y coordinates of training data
   - Note: This is a variable-length array based on user input

  6. Collecting Training Data Points

   1 printf("Now, enter continuously values in the form x,y."
   2        " You will enter %zd of them\n",
   3        train_size);
   4 for (i = 0; i < train_size; i++) {
   5   printf("Enter point #%zd> ", i + 1);
   6   scanf("%lf,%lf", &x[i], &y[i]);
   7 }
   - Prompt user to enter data points in x,y format
   - Loop through and collect each point
   - Store x and y values in corresponding arrays

  7. Initialize Model Parameters

   1 double gradient = 1.0, intercept = 0.0;
   - Initialize slope (gradient) and y-intercept of the line
   - These will be adjusted during training

  8. Training Configuration

    1 printf("For how many epochs should we train? default 5000\n> ");
    2 size_t epochs;
    3 scanf("%zd", &epochs);
    4 if (epochs == 0)
    5   epochs = 5000; // default value
    6
    7 printf("What should be learn rate of the model? default 0.01\n> ");
    8 double learn_rate;
    9 scanf("%lf", &learn_rate);
   10 if (learn_rate == 0)
   11   learn_rate = 0.01; // default
   - Get number of training iterations (epochs) from user
   - Set default if user enters 0
   - Get learning rate from user
   - Set default if user enters 0

  9. Logging Configuration

   1 size_t log_epoch = epochs / 100;
   - Calculate interval for logging progress (every 1% of total epochs)

  10. Training Loop

    1 for (size_t epoch = 0; epoch < epochs; epoch++) {
    2   double sum_errors = 0;
    3   for (i = 0; i < train_size; i++) {
    4     // y = mx + c
    5     double y_guess = gradient * x[i] + intercept;
    6     // find difference with actual value
    7     double error = y_guess - y[i];
    8     if (error == 0)
    9       continue;d
   10     sum_errors += fabs(error);
   11     // improve the gradient
   12     gradient -= learn_rate * x[i] * error;
   13     // improve the intercept
   14     intercept -= learn_rate * error;
   15   }
   - Outer loop: iterate through training epochs
   - Inner loop: process each training example
   - Calculate predicted y value using current model: y = mx + c
   - Compute error as difference between prediction and actual value
   - Skip adjustments if error is zero (no correction needed)
   - Accumulate absolute error to track overall loss
   - Adjust gradient (slope) based on error and learning rate
   - Adjust intercept based on error and learning rate

  11. Progress Logging

   1 if (epoch % log_epoch == 0)
   2   printf("epoch %zd, loss is %.4lf equation is y = %.2lfx + %.2lf\n",
   3          epoch + 1, sum_errors, gradient, intercept);
   - Print progress every 1% of epochs
   - Shows current epoch, total loss, and current equation

  12. Early Stopping Condition

   1 if (sum_errors < 0.000001) {
   2   printf("Stopping to train the model because the error reduced alot");
   3   break;
   4 }
   - Stop training if error gets very small
   - Indicates model has converged to a solution

  13. Final Result

   1 printf("The equation of the line is y = %.2lfx + %.3lf", gradient, intercept);
   2 return 0;
   3 }
   - Output final equation after training
   - Return success code

  Explanation of the Algorithm

  In the video, explain that this implements gradient descent to minimize the error between predicted and
  actual values. The algorithm:
   1. Makes a prediction using current parameters
   2. Calculates the error
   3. Adjusts parameters slightly in the direction that reduces error
   4. Repeats many times until the model fits the data well

  Key Programming Concepts to Highlight

   1. Variable-Length Arrays (VLAs): Arrays whose size is determined at runtime
   2. Gradient Descent: Optimization algorithm that iteratively improves parameters
   3. Learning Rate: Controls how big of steps to take during parameter updates
   4. Epochs: Complete passes through the training dataset


  This tutorial covers all aspects of implementing a simple linear regression model from scratch, making it a
  valuable resource for viewers interested in machine learning fundamentals and C programming.
