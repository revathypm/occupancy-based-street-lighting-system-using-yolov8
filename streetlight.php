<?php 
$hostname = "localhost"; 
$username = "root"; 
$password = ""; 
$database = "street_light"; 

$conn = mysqli_connect($hostname, $username, $password, $database);

if (!$conn) { 
	die("Connection failed: " . mysqli_connect_error()); 
} 
else {
    echo "Database connection is OK<br>";
}

if(isset($_GET['s1']) && isset($_GET['s2'])) {
    $s1 = $_GET['s1'];
    $s2 = $_GET['s2'];

    $sql = "INSERT INTO light_tb (led1,led2) VALUES ('$s1', '$s2')"; 

    if ($conn->query($sql) === TRUE) {
        echo "Values inserted in MySQL database table.";
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
}
else {
    echo "Not all required values are received from the GET request.";
}

$conn->close();
?>
