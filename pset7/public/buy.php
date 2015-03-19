<?php
	//buy.php
	//Initiates a buy of shares
	//Uses templates buy_confirm and buy_success
	//CS50 | PSET7
	//Notes:
	//Stock to buy passed from quote.php
	
	require("../includes/config.php");
	
	if(isset($_POST["confirm"]) && isset($_POST["quantity"]) && isset($_POST["stock"]))
	{
		if(preg_match("/^\d+$/", $_POST["quantity"]))
		{
			//Recheck price (can't trust a submitted price)!
			$quote = lookup($_POST["stock"]);
			
			//Check for the current cash balance
			$sql_command = "SELECT cash FROM users WHERE id = ?";
			$result = query($sql_command, $_SESSION['id']);
		
			if($result === false)
			{
				apologize("Unable to access the database, please try again later");
			}
			
			//Check user has enough dough!
			$cost = $_POST["quantity"] * $quote["price"];
			if($cost <= $result[0]["cash"])
			{
				//Initiate the buy!
				$sql_command = "INSERT INTO shares (id, stock, quantity)
								VALUES (?, ?, ?)
								ON DUPLICATE KEY
								UPDATE quantity = quantity + VALUES(quantity)";
				$result = query($sql_command, $_SESSION['id'], strtoupper($_POST["stock"]), $_POST["quantity"]);
				
				if($result === false)
				{
					apologize("Error adding your stock");
				}
				
				$sql_command = "UPDATE users
								SET cash = cash - ?
								WHERE id = ?";
				$result = query($sql_command,  $cost, $_SESSION["id"]);
				
				if($result === false)
				{
					apologize("Error subtracting the price");
				}				
				
				//Check for the current cash balance
				$sql_command = "SELECT cash FROM users WHERE id = ?";
				$result = query($sql_command, $_SESSION['id']);
		
				if($result === false)
				{
					apologize("Unable to access the database, please try again later");
				}
				$cash = $result[0]["cash"];				
				
				//Log the buy in user's history
				$sql_command = "INSERT INTO history
								(id, quantity, symbol, price, isbuy)
								VALUES (?, ?, ?, ?, true)";
				$result = query($sql_command,
					$_SESSION["id"],
					$_POST["quantity"],
					strtoupper($_POST["stock"]),
					$quote["price"]
				);
				
				if($result === false)
				{
					apologize("Unable to log your purchase into your history");
				}
						
				render("buy_success.php", [
					"title"=>"Congratulations!",
					"quantity"=>$_POST["quantity"],
					"cost"=>$cost,
					"quote"=>$quote,
					"cash"=>$cash
				]);
			}
			else
			{
				apologize("We can't sell to paupers");
			}
		}
		else
		{
			apologize("You can only buy whole units of shares, here");
		}
	}
	else if(isset($_POST["buy"]) && isset($_POST["stock"]))
	{
		//Check for the current cash balance
		$sql_command = "SELECT cash FROM users WHERE id = ?";
		$result = query($sql_command, $_SESSION['id']);
		
		if($result === false)
		{
			apologize("Unable to access the database, please try again later");
		}
	
		//Check stock information
		$quote = lookup($_POST["stock"]);
		
		//Render the buy-confirmation view		
		render("buy_confirm.php",[
			"title"=>"Confirm your purchase",
			"quote"=>$quote,
			"cash"=>number_format($result[0]["cash"], 2)
		]);
	}
	else
	{
		apologize("You could have had a lovely quote, if only you'd passed a stock symbol.");
	}
