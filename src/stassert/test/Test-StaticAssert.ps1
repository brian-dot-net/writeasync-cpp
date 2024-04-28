[CmdletBinding()]
param(
	[Parameter(Mandatory=$true)]
	[string]$Symbol,
	[Parameter(Mandatory=$true)]
	[string]$Pattern,
	[Parameter(Mandatory=$true)]
	[string]$WorkingDirectory,
	[Parameter(Mandatory=$false)]
	[string]$CompileCommands = 'compile_commands.json',
	[Parameter(Mandatory=$false)]
	[string]$TestFile = 'stassert_test.cpp'
)

if (!(Test-Path $WorkingDirectory)) {
	throw "Working directory '$WorkingDirectory' not found"
}

Push-Location $WorkingDirectory
Write-Host "Set working directory '$WorkingDirectory'"

if (!(Test-Path $CompileCommands)) {
	throw "Compile commands file '$CompileCommands' not found"
}

$item = Get-Content $CompileCommands |
	ConvertFrom-Json | Where-Object { $_.file -like "*$TestFile"}

if (!$item) {
	throw "Could not find compile command for test file '$TestFile'"
}

$command = $item.command -replace '@\S+\.modmap ', ''
$command += " /D$Symbol"
Write-Host "Invoking compilation command: $command"
$output = Invoke-Expression $command
if ($LASTEXITCODE -eq 0) {
	throw "Compilation unexpectedly succeeded"
}

Write-Host "Output: $output"

$matched = $false
$output | Select-String -Pattern $Pattern | ForEach-Object {
	$matched = $true
	Write-Host "Found matching output line: $_"
}

if (!$matched) {
	throw "Did not find output line matching '$Pattern'"
}