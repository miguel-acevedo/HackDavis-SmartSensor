<?php
 
require("db.php");
 
if(isset($_GET['floor']) && isset($_GET['room']) && isset($_GET['count']))
{
    $floor = $_GET['floor'];
	$room = $_GET['room'];
	$count = $_GET['count'];
	
	//$query = mysql_query("SELECT * FROM people where id = 0");
	echo $floor . " ". $room . " " . $count;
	
	mysql_query("insert into occupancy (floor, room, count) VALUES (". $floor .", ".$room.", ".$count.")");
}
else{
	echo "Error: Need variables floor, room, event.";
}
 
 
 /*
$query = mysql_query("SELECT * FROM people where id = 0");
$num = mysql_num_rows($query);
 
for ($i = 0; $i < $num; $i++)
{
    if($data = mysql_fetch_array($query))
    {
        $firstname = $data['firstname'];
        $lastname = $data['lastname'];
         
    }
}
 
echo $firstname . " " . $lastname;
*/
 
 
?>