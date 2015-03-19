<?php

	//Password.php - change the user's password
	//PSET7 | CS50

	require("../includes/config.php");

	if(isset($_POST["password"]) && isset($_POST["confirm"]))
	{
		$errors = "";
        //Make sure a password was given
        if($_POST['password'] === "")
        {
        	if($errors === "")
	            $errors .= "No password was given";
	        else
	        	$errors .= " and no password was given";
        }
        //Make sure the password matches the confirmation
        else if($_POST['confirm'] !== $_POST['password'])
        {
        	if($errors === "")
	            $errors .= "Password and confirmation must be the same";
	        else
	        	$errors .= " and also, the password doesn't match the confirmation";
        }
        
        
        //Check to see if there were any errors, else we can add user
        if($errors !== "")
        {
            //Pass errors to apology function
            $errors .= ".";
            apologize($errors);
        }
        else
        {
            //We have a username and confirmed password
            $sql_command = "UPDATE users
            				SET hash = ?
							WHERE id = ?";
							
			//Execute the sql wrapper function with a hash of the password and the username
            $result = query($sql_command, crypt($_POST['password']), $_SESSION["id"]);
            
            //Process any errors
            if($result === false)
            {
            	apologize("Unable to change your password, try again later");
            }
            else
            {
            	render("password_success.php", ["title"=>"Password changed"]);
            }
		}
		
	}
	else
	{
		render("password_change.php", ["title"=>"Change your password"]);
	}
