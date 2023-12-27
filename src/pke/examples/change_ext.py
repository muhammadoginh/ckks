import os

def get_file_extension(file_path):
    # Get the file extension from the file path
    _, extension = os.path.splitext(file_path)
    return extension.lower()  # Convert to lowercase for case-insensitivity

def add_extension_to_files(folder_path, extension):
    try:
        # List all files in the folder
        files = os.listdir(folder_path)

        # Loop through each file and add the extension
        for file in files:
            old_path = os.path.join(folder_path, file)
            
            # Check if the item is a file (not a directory)
            if get_file_extension(old_path) == '.cpp' and os.path.isfile(old_path):
                new_path = os.path.join(folder_path, f"{file}.{extension}")
                
                # Rename the file with the new extension
                os.rename(old_path, new_path)
                print(f"File renamed successfully: {file} to {file}.{extension}")
            else:
                print("nothing change")
    except OSError as e:
        print(f"Error: {e}")

# Example usage:
folder_path = "."
extension_to_add = "txt"

add_extension_to_files(folder_path, extension_to_add)