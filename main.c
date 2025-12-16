 #include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to hold training data
typedef struct {
    double *x_values;
    double *y_values;
    size_t size;
} TrainingData;

// Structure to hold model parameters
typedef struct {
    double gradient;
    double intercept;
} LinearModel;

/**
 * Initialize training data with given size
 */
TrainingData* initialize_training_data(size_t size) {
    if (size == 0) return NULL;

    TrainingData *data = malloc(sizeof(TrainingData));
    if (!data) {
        fprintf(stderr, "Error: Failed to allocate memory for training data.\n");
        return NULL;
    }

    data->x_values = malloc(size * sizeof(double));
    data->y_values = malloc(size * sizeof(double));
    if (!data->x_values || !data->y_values) {
        fprintf(stderr, "Error: Failed to allocate memory for data arrays.\n");
        free(data->x_values);
        free(data->y_values);
        free(data);
        return NULL;
    }

    data->size = size;
    return data;
}

/**
 * Free allocated training data
 */
void free_training_data(TrainingData *data) {
    if (data) {
        free(data->x_values);
        free(data->y_values);
        free(data);
    }
}

/**
 * Get the number of training points from user input
 */
bool get_training_size(size_t *train_size) {
    printf("Welcome to linear regressor!\n");
    printf("Let's start training the model\n");
    printf("What number of graph points do you have?\n> ");

    int result = scanf("%zd", train_size);
    if (result != 1 || *train_size <= 0) {
        fprintf(stderr, "Invalid input. Number of points must be positive.\n");
        return false;
    }
    return true;
}

/**
 * Collect training data points from user
 */
bool collect_training_points(TrainingData *data) {
    printf("Now, enter values in the form x,y. You will enter %zd of them\n", data->size);

    for (size_t i = 0; i < data->size; i++) {
        printf("Enter point #%zd> ", i + 1);
        int result = scanf("%lf,%lf", &data->x_values[i], &data->y_values[i]);
        if (result != 2) {
            fprintf(stderr, "Error: Invalid input format. Please enter values in x,y format.\n");
            return false;
        }
    }
    return true;
}

/**
 * Get training hyperparameters from user
 */
bool get_hyperparameters(size_t *epochs, double *learning_rate) {
    printf("For how many epochs should we train? default 5000\n> ");
    int result = scanf("%zd", epochs);
    if (result != 1 || *epochs <= 0)
        *epochs = 5000; // default value

    printf("What should be learning rate of the model? default 0.01\n> ");
    result = scanf("%lf", learning_rate);
    if (result != 1 || *learning_rate <= 0.0)
        *learning_rate = 0.01; // default

    return true;
}

/**
 * Perform a single iteration of gradient descent
 */
double train_step(TrainingData *data, LinearModel *model, double learning_rate) {
    double sum_errors = 0.0;
    double gradient_sum = 0.0;
    double intercept_sum = 0.0;

    // Calculate gradients for entire dataset
    for (size_t i = 0; i < data->size; i++) {
        // Calculate prediction: y = mx + c
        double y_prediction = model->gradient * data->x_values[i] + model->intercept;

        // Calculate error
        double error = y_prediction - data->y_values[i];
        sum_errors += fabs(error);

        // Accumulate gradient and intercept adjustments
        gradient_sum += error * data->x_values[i];
        intercept_sum += error;
    }

    // Apply accumulated adjustments to model parameters
    model->gradient -= learning_rate * gradient_sum / data->size;
    model->intercept -= learning_rate * intercept_sum / data->size;

    return sum_errors;
}

/**
 * Train the linear regression model using gradient descent
 */
void train_model(TrainingData *data, LinearModel *model, size_t epochs, double learning_rate) {
    size_t log_interval = (epochs > 100) ? epochs / 100 : 1;  // Log every 1% of epochs or once per epoch if less than 100

    for (size_t epoch = 0; epoch < epochs; epoch++) {
        double sum_errors = train_step(data, model, learning_rate);

        // Log progress at intervals
        if ((epoch + 1) % log_interval == 0) {
            printf("Epoch %zu, average loss is %.4lf, equation is y = %.4lfx + %.4lf\n",
                   epoch + 1, sum_errors/data->size, model->gradient, model->intercept);
        }

        // Early stopping condition
        if (sum_errors / data->size < 0.000001) {
            printf("Stopping training early - convergence achieved at epoch %zu\n", epoch + 1);
            break;
        }
    }
}

/**
 * Main function implementing linear regression using gradient descent
 */
int main() {
    size_t train_size;

    // Get training size from user
    if (!get_training_size(&train_size)) {
        return EXIT_FAILURE;
    }

    // Initialize training data
    TrainingData *training_data = initialize_training_data(train_size);
    if (!training_data) {
        return EXIT_FAILURE;
    }

    // Collect training points from user
    if (!collect_training_points(training_data)) {
        free_training_data(training_data);
        return EXIT_FAILURE;
    }

    // Get hyperparameters from user
    size_t epochs;
    double learning_rate;
    if (!get_hyperparameters(&epochs, &learning_rate)) {
        free_training_data(training_data);
        return EXIT_FAILURE;
    }

    // Initialize model parameters
    LinearModel model = {1.0, 0.0};  // Start with gradient=1.0, intercept=0.0

    // Train the model
    printf("\nStarting training...\n");
    train_model(training_data, &model, epochs, learning_rate);

    // Output final result
    printf("\nThe equation of the line is y = %.4lfx + %.4lf\n", model.gradient, model.intercept);

    // Clean up
    free_training_data(training_data);

    return EXIT_SUCCESS;
}
