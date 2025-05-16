<?php
// Database connection settings
$servername = "localhost";
$username = "root"; // Change this if you have a different username
$password = "";     // Change this if you have a password
$dbname = "feastandfest"; // Make sure this database exists

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

// Retrieve and sanitize form inputs
$name = htmlspecialchars($_POST['name']);
$email = htmlspecialchars($_POST['email']);
$password = password_hash($_POST['password'], PASSWORD_DEFAULT); // Hashing the password

// Prepare SQL statement to prevent SQL injection
$stmt = $conn->prepare("INSERT INTO users (name, email, password) VALUES (?, ?, ?)");
$stmt->bind_param("sss", $name, $email, $password);

if ($stmt->execute()) {
  echo "Registration successful!";
} else {
  echo "Error: " . $stmt->error;
}

// Close connections
$stmt->close();
$conn->close();
?>
