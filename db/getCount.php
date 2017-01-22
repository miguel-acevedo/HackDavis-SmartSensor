<?php
 
require("db.php");

$return_arr = array();

$building = $_GET['building']; // Name of the building your trying to get data from.
$floor = $_GET['floor'];

$query = mysqli_query("SELECT * FROM occupancy where building='".$building."' and floor=".$floor." ORDER BY time DESC"); 

$num = mysqli_num_rows($query);

$found = array();
 
for ($i = 0; $i < $num; $i++)
{
    if($data = mysqli_fetch_array($query))
    {
		$row_array['time'] = $data['time'];
		$row_array['room'] = $data['room'];
		$row_array['count'] = $data['count'];
		
		if (in_array($row_array['room'], $found)) continue;
		
		$found[$i] = $data['room'];

		array_push($return_arr,$row_array);      
    }
}

echo json_encode($return_arr);
 
 
?>