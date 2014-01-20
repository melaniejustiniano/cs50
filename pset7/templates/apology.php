<ul class="nav nav-pills">
    <li><a href="quote.php">Quote</a></li>
    <li><a href="buy.php">Buy</a></li>
    <li><a href="sell.php">Sell</a></li>
    <li><a href="history.php">History</a></li>
    <li><a href="logout.php"><strong>Log Out</strong></a></li>
</ul>

<p class="lead text-error">
    Sorry!
</p>
<p class="text-error">
    <?= htmlspecialchars($message) ?>
</p>

<a href="javascript:history.go(-1);">Back</a>
