<?php

    // configuration
    require("../includes/config.php");
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // lookup stock information
        $stock = lookup($_POST["symbol"]);
        if ($stock === false)
            apologize("Could not look up stock! \n");
        
        // change decimal format
        $stock["price"] = number_format($stock["price"], 2);
        
        // new page for output
        require("../templates/header.php");
        echo "A share of " . $stock["name"] . ' (' . $stock["symbol"]
             . ') ' . "costs <b>$ " . $stock["price"] . "</b>.";
        require("../templates/footer.php");
    }
  
    else
    {
        // else render form
        render("quote_form.php", ["title" => "Get Quote"]);
    }
?>
