<?php
 
require("db.php");
 
if(isset($_GET['floor']) && isset($_GET['room']) && isset($_GET['count']))
{
    $floor = $_GET['floor'];
	$room = $_GET['room'];
	$count = $_GET['count'];
	
	//$query = mysqlii_query("SELECT * FROM people where id = 0");
	echo $floor . " ". $room . " " . $count;
	
	mysqli_query("insert into occupancy (floor, room, count) VALUES (". $floor .", ".$room.", ".$count.")");
}
else{
	echo "Error: Need variables floor, room, event.";
}
 
 
 /*
$query = mysqli_query("SELECT * FROM people where id = 0");
$num = mysqli_num_rows($query);
 
for ($i = 0; $i < $num; $i++)
{
    if($data = mysqli_fetch_array($query))
    {
        $firstname = $data['firstname'];
        $lastname = $data['lastname'];
         
    }
}
 
echo $firstname . " " . $lastname;
*/
 
 
?>