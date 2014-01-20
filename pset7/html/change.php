<?
    // configuration
    require("../includes/config.php");
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if ($_POST["oldpassword"] == NULL)
            apologize("Empty password field!");
        
        if ($_POST["newpassword"] == NULL)
            apologize("Empty password field!");
            
        if ($_POST["confirmation"] == NULL)
            apologize("Empty confirmation field!");

        if ($_POST["newpassword"] != $_POST["confirmation"])
            apologize("Passwords don't match!");
        
        $rows = query("SELECT * FROM users WHERE id = ?",
                       $_SESSION["id"]);
                       
        // if we found user, check password
        if (count($rows) == 1)
        {
            // first (and only) row
            $row = $rows[0];

            // compare hash of user's input against hash that's in database
            if (crypt($_POST["oldpassword"], $row["hash"]) == $row["hash"])
            {
                $result = query("UPDATE users SET hash = ? WHERE id = ?",
                                 crypt($_POST["newpassword"]), $_SESSION["id"]);

                // redirect to portfolio
                redirect("/");
            }
        }

        // else apologize
        apologize("Incorrect password.");
         
    }
    
    else   
    {
        render("change_form.php", ["title" => "Change Password"]);
    }
?>
