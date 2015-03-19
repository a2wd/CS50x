<?php

	//History.php - retrieve a history of a user's transactions
	require("../includes/config.php");
	
	$result = query("SELECT * FROM history WHERE id = ?", $_SESSION['id']);
	$cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION['id']);	
	
	if($result === false || $cash === false)
	{
		apologize("Sorry, couldn't find your history, maybe there's a pigeon in the vault");
	}
	else
	{
		render("show_history.php", [
			"cash"=> $cash,
			"title"=>"Your history",
			"history"=>$result
		]);
	}
