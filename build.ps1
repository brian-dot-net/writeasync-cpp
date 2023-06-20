param(
  [ValidateSet('debug', 'release')]
  [string] $Configuration = 'debug',
  [switch] $NoTest
)

$ErrorActionPreference = 'Stop'

if (!$Env:VSCMD_VER) {
  Write-Error "Please run this from a VS Developer Powershell window."
}

$preset = "x64-$Configuration"

cmake.exe --preset $preset
if ($LASTEXITCODE -ne 0) {
  Write-Error "Configure failed with code $LASTEXITCODE"
}

cmake.exe --build --preset $preset
if ($LASTEXITCODE -ne 0) {
  Write-Error "Build failed with code $LASTEXITCODE"
}

if (!$NoTest) {
  ctest.exe --preset $preset
  if ($LASTEXITCODE -ne 0) {
    Write-Error "Test failed with code $LASTEXITCODE"
  }
}