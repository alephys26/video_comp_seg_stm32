import numpy as np
def retrieve_model_parameters(file_path, weight_shapes):
    """
    Retrieve weight matrices from the text file.

    Args:
        file_path (str): Path to the text file containing model parameters.
        weight_shapes (dict): A dictionary with module names as keys and expected weight shapes as values.

    Returns:
        dict: A dictionary where keys are module names and values are weight matrices.
    """
    parameters = {}

    # Initialize variables to keep track of current module
    current_module_name = None
    current_weights = []
    in_weights_section = False

    # Open the file for reading
    with open(file_path, 'r') as f:
        # Read file line by line
        for line in f:
            # Check if the line starts with "Module name:"
            if line.startswith("Module name:"):
                # Store the previous module's parameters (if any)
                if current_module_name is not None:
                    # Convert the accumulated weights to a numpy array according to expected shape
                    expected_shape = weight_shapes.get(current_module_name, None)
                    if expected_shape is not None:
                        current_weights = [x for x in current_weights if len(x) != 0]
                        weights_array = np.array(current_weights).reshape(expected_shape)
                        parameters[current_module_name] = weights_array
                    else:
                        print(f"Warning: No expected shape defined for module '{current_module_name}'.")
                
                # Extract the new module name
                current_module_name = line.strip().split(":")[1].strip()
                
                # Reset the weights list for the new module
                current_weights = []
                in_weights_section = False

            # Check if the line starts with "Weights:"
            elif line.startswith("Weights:"):
                # We are in the weights section
                in_weights_section = True
            elif in_weights_section:
                # If we are in the weights section, read the weights
                # Remove leading and trailing whitespace and square brackets
                cleaned_line = line.strip().strip('[]')

                # If the line is empty, skip it
                if not cleaned_line:
                    continue

                # Convert the line to a numpy array
                weights_row = np.fromstring(cleaned_line, sep=' ')

                # Append the weights row to the current weights list
                current_weights.append(weights_row)

    # Store the last module's parameters if any
    if current_module_name is not None:
        expected_shape = weight_shapes.get(current_module_name, None)
        if expected_shape is not None:
            current_weights = [x for x in current_weights if len(x) != 0]
            weights_array = np.array(current_weights).reshape(expected_shape)
            parameters[current_module_name] = weights_array
        else:
            print(f"Warning: No expected shape defined for module '{current_module_name}'.")

    return parameters

# Define a dictionary of expected weight shapes for each module
weight_shapes = {
    'conv_block_down1.0': (64, 3, 3, 3),  # Shape for conv_block_down1.0
    'conv_block_down1.2': (64, 64, 3, 3), # Shape for conv_block_down1.2
    'conv_block_down2.0': (128, 64, 3, 3), # Shape for conv_block_down2.0
    'conv_block_down2.2': (128, 128, 3, 3), # Shape for conv_block_down2.2
    'conv_block_up1.0': (64, 192, 3, 3), # Shape for conv_block_up1.0
    'conv_block_up1.2': (64, 64, 3, 3), # Shape for conv_block_up1.2
    'conv_last': (32, 64, 1, 1) # Shape for conv_last
    # Add other expected shapes here
}

# Specify the path to the text file containing model parameters
file_path = r"C:\Study\III year\Sem2\ES\test_3.txt"

# Retrieve the parameters from the file
parameters = retrieve_model_parameters(file_path, weight_shapes)

# Print the parameters for each module (optional)
for module_name, weights in parameters.items():
    print(f"Module: {module_name}")
    print(f"Weights shape: {weights.shape}")