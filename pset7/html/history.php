<?
    // configuration
    require("../includes/config.php");
    
    // use user information
    $rows = query("SELECT * FROM history WHERE id = ?",
                   $_SESSION["id"]);
    
    // render page with user data
    render("history_page.php", ["title" => "History", "rows" => $rows]);
?>
