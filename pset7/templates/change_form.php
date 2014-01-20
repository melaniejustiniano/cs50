<ul class="nav nav-pills">
    <li><a href="quote.php">Quote</a></li>
    <li><a href="buy.php">Buy</a></li>
    <li><a href="sell.php">Sell</a></li>
    <li><a href="history.php">History</a></li>
    <li><a href="logout.php"><strong>Log Out</strong></a></li>
</ul>

<form action="change.php" method="post">
    <fieldset>
        <div class="control-group">
            <input name="oldpassword" placeholder="Old Password" type="password"/>
        </div>
        <div class="control-group">
            <input name="newpassword" placeholder="New Password" type="password"/>
        </div>
        <div class="control-group">
            <input name="confirmation" placeholder="New Password" type="password"/>
        </div>
        <div class="control-group">
            <button type="submit" class="btn">Change Password</button>
        </div>
    </fieldset>
</form>
