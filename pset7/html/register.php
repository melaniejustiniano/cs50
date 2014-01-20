<?php
    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // if empty fields and check password fields
        if ($_POST["password"] == NULL)
            apologize("Empty password field! \n");
        if ($_POST["confirmation"] == NULL)
            apologize("Empty confirmation field! \n");
        if ($_POST["password"] != $_POST["confirmation"])
            apologize("Passwords don't match! \n");
        if ($_POST["username"] == NULL)
            apologize("Empty username field! \n");
        
        // create user in table
        $result = query("INSERT INTO users (username, hash, cash) VALUES
                         (?, ?, 10000.00)", $_POST["username"],
                         crypt($_POST["password"]));
        if ($result === false)
            apologize("Could not register! \n");
        
        // set user id
        $rows = query("SELECT LAST_INSERT_ID() AS id");
        $id = $rows[0]["id"];
        
        // store user id as session id
        $_SESSION["id"] = $id;
        
        // redirect to index
        redirect("index.php");
    }
    else
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }
?>
