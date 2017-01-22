<?php
require("db.php");

$return_arr = array();

$building = $_GET['building']; // Name of the building your trying to get data from.

$query = mysqli_query("SELECT * FROM energy where type='".$building."'"); 

$num = mysqli_num_rows($query);
 
for ($i = 0; $i < $num; $i++)
{
    if($data = mysqli_fetch_array($query))
    {
		$row_array['time'] = $data['time'];
		$row_array['power'] = $data['power'];

		array_push($return_arr,$row_array);      
    }
}
$query = mysqli_query("SELECT * FROM occupancy where building='currant'"); 

$num = mysqli_num_rows($query);
 
for ($i = 0; $i < $num; $i++)
{
    if($data = mysqli_fetch_array($query))
    {
		$new_array['time'] = $data['time'];
		$new_array['count'] = $data['count'];

		array_push($return_arr,$new_array);      
    }
}

echo json_encode($return_arr);

?>